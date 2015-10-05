#include <stdexcept>
#include <sstream>
#include "gambit/ColliderBit/colliders/SpecializablePythia.hpp"
#include "gambit/ColliderBit/ColliderBit_macros.hpp"

/*#include "Pythia8/Sigma_MC4BSM_2012_UFO_gg_uvuvx.h"
#include "Pythia8/Sigma_MC4BSM_2012_UFO_qq_uvuvx.h"
#include "Pythia8/Sigma_MC4BSM_2012_UFO_qq_evevx.h"
#include "Pythia8/Sigma_MC4BSM_2012_UFO_qq_p1p2.h"
#include "Pythia8/Sigma_MC4BSM_2012_UFO_qq_p2p2.h"
#include "Pythia8/Sigma_MC4BSM_2012_UFO_qq_p1p1.h"*/

namespace Gambit {
  namespace ColliderBit {

    /// @name Pythia specialization functions
    //@{
      /// @brief No specialization - pure external settings only.

    namespace Pythia_UserModel{
      void init(SpecializablePythia* specializeMe) {}
	
    }
    
      namespace Pythia_external {
        void init(SpecializablePythia* specializeMe) { }
      }

      /// @brief Specializes for SUSY @ 8TeV LHC
      namespace Pythia_SUSY_LHC_8TeV {
        void init(SpecializablePythia* specializeMe) {
          // Basic setup for a general SUSY LHC run
          specializeMe->addToSettings("Beams:eCM = 8000");
          specializeMe->addToSettings("Main:numberOfEvents = 1000");
          specializeMe->addToSettings("Main:timesAllowErrors = 1000");
          // Default to SUSY with all subprocesses
          specializeMe->addToSettings("SUSY:all = on");

          // Random seed setup
          specializeMe->addToSettings("Random:setSeed = on");
        }
      }

      /// @brief Specializes for SUSY @ 8TeV LHC - only gluino squark processes
      namespace Pythia_glusq_LHC_8TeV {
        void init(SpecializablePythia* specializeMe) {
          /// @note "Inherit" another specialization by calling it also.
          Pythia_SUSY_LHC_8TeV::init(specializeMe);

          specializeMe->addToSettings("SUSY:idA = 1000021");
          specializeMe->addToSettings("SUSY:idVecB = 1000001, 1000002, 1000003, 1000004, 2000001, 2000002, 2000003, 2000004");
        }
      }
    //@}


    void SpecializablePythia::init_external(const std::string pythiaDocPath,
                                     const std::vector<std::string>& externalSettings,
                                     const SLHAea::Coll* slhaea, std::ostream& os) {

        _pythiaInstance = new Pythia8::Pythia(pythiaDocPath, false);

      // Special version of the init function for user defined models
      // Needs to directly construct the new matrix elements (rather than use flags)
      
        // Settings acquired externally (ex from a gambit yaml file)
        for(const auto command : externalSettings) {
          _pythiaSettings.push_back(command);
        }

        // Specialized settings:
        _specialInit(this);

        // Use all settings to instantiate and initialize Pythia
        for(const auto command : _pythiaSettings)
          _pythiaInstance->readString(command);

        if(!_pythiaInstance) throw InitializationError();

	//User makes the matrix elements here
	// MJW: need to reintroduce once Anders fixes bossed Pythia
	/*_pythiaInstance->setSigmaPtr(new Sigma_MC4BSM_2012_UFO_gg_uvuvx()); 
	_pythiaInstance->setSigmaPtr(new Sigma_MC4BSM_2012_UFO_qq_uvuvx()); 
	_pythiaInstance->setSigmaPtr(new Sigma_MC4BSM_2012_UFO_qq_evevx()); 
	_pythiaInstance->setSigmaPtr(new Sigma_MC4BSM_2012_UFO_qq_p1p2()); 
	_pythiaInstance->setSigmaPtr(new Sigma_MC4BSM_2012_UFO_qq_p2p2()); 
	_pythiaInstance->setSigmaPtr(new Sigma_MC4BSM_2012_UFO_qq_p1p1()); */
	
        // Send along the SLHAea::Coll pointer, if it exists
        if(slhaea)
          _pythiaInstance->slhaInterface.slha.setSLHAea(slhaea);

	
	
        _pythiaInstance->init(os);
      }
    
    /// @name SpecializablePythia definitions
    //@{
      void SpecializablePythia::init(const std::string pythiaDocPath,
                                     const std::vector<std::string>& externalSettings,
                                     const SLHAea::Coll* slhaea, std::ostream& os) {
        _pythiaInstance = new Pythia8::Pythia(pythiaDocPath, false);

        // Settings acquired externally (ex from a gambit yaml file)
        for(const auto command : externalSettings) {
          _pythiaSettings.push_back(command);
        }

        // Specialized settings:
        _specialInit(this);

        // Use all settings to instantiate and initialize Pythia
        for(const auto command : _pythiaSettings)
          _pythiaInstance->readString(command);

        if(!_pythiaInstance) throw InitializationError();

        // Send along the SLHAea::Coll pointer, if it exists
        if(slhaea)
          _pythiaInstance->slhaInterface.slha.setSLHAea(slhaea);

        _pythiaInstance->init(os);
      }

      void SpecializablePythia::resetSpecialization(const std::string& specName) {
        clear();
        #define IF_X_SPECIALIZEX(X) if (specName == #X) { _specialInit = X::init; return; }
        IF_X_SPECIALIZEX(Pythia_external)
        IF_X_SPECIALIZEX(Pythia_SUSY_LHC_8TeV)
        IF_X_SPECIALIZEX(Pythia_glusq_LHC_8TeV)
        #undef IF_X_SPECIALIZEX
        // default to a Pythia instance configured entirely by external (yaml) settings:
        _specialInit = Pythia_external::init;
        std::cout<<"\n\n\n"
                 <<"COLLIDERBIT WARNING: Pythia named "<<specName<<" is not coded in SpecializablePythia."
                 <<"                     Now trying to configure Pythia entirely by yaml input..."
                 <<"\n\n\n";
      }
    //@}
  }
}
