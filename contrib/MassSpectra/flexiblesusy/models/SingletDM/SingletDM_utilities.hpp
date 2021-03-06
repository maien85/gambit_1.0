// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Sat 27 Aug 2016 12:43:02

#ifndef SingletDM_UTILITIES_H
#define SingletDM_UTILITIES_H

#include "SingletDM_mass_eigenstates.hpp"
#include "SingletDM_info.hpp"
#include "wrappers.hpp"

#include <Eigen/Core>
#include <string>
#include <vector>
#include <valarray>
#include <utility>

namespace softsusy {
class QedQcd;
}

namespace flexiblesusy {

struct SingletDM_observables;
class Physical_input;

class SingletDM_parameter_getter {
public:
   Eigen::ArrayXd get_parameters(const SingletDM_mass_eigenstates& model) {
      return model.get();
   }
   std::vector<std::string> get_parameter_names() const {
      using namespace SingletDM_info;
      return std::vector<std::string>(parameter_names,
                                      parameter_names + NUMBER_OF_PARAMETERS);
   }
   std::vector<std::string> get_particle_names() const {
      using namespace SingletDM_info;
      return std::vector<std::string>(particle_names,
                                      particle_names + NUMBER_OF_PARTICLES);
   }
   std::vector<std::string> get_mass_names() const {
      using namespace SingletDM_info;
      std::vector<std::string> masses;
      for (unsigned i = 0; i < NUMBER_OF_PARTICLES; i++) {
         for (unsigned m = 0; m < particle_multiplicities[i]; m++) {
            masses.push_back(
               std::string("M") + particle_names[i] +
               (particle_multiplicities[i] == 1 ? "" : "("
                + std::to_string(static_cast<unsigned long long>(m)) + ")"));
         }
      }
      return masses;
   }
   std::vector<std::string> get_mixing_names() const {
      using namespace SingletDM_info;
      return std::vector<std::string>(particle_mixing_names,
                                      particle_mixing_names + NUMBER_OF_MIXINGS);
   }
   std::vector<std::string> get_input_parameter_names() const {
      using namespace SingletDM_info;
      return std::vector<std::string>(input_parameter_names,
                                      input_parameter_names + NUMBER_OF_INPUT_PARAMETERS);
   }
   std::size_t get_number_of_masses() const {
      using namespace SingletDM_info;
      return NUMBER_OF_MASSES;
   }
};

class SingletDM_spectrum_plotter {
public:
   SingletDM_spectrum_plotter();
   ~SingletDM_spectrum_plotter() {}

   void extract_spectrum(const SingletDM_mass_eigenstates&);
   void write_to_file(const std::string&) const;

private:
   struct TParticle {
      std::string name;
      std::string latex_name;
      std::valarray<double> masses;
      TParticle(const std::string& name_, const std::string& latex_name_,
                const std::valarray<double>& masses_)
         : name(name_)
         , latex_name(latex_name_)
         , masses(masses_)
         {}
   };
   typedef std::vector<TParticle> TSpectrum;
   TSpectrum spectrum;
   double scale;
   unsigned width;

   void write_spectrum(const TSpectrum&, std::ofstream&) const;
   static std::valarray<double> to_valarray(double);
   template <class Scalar, int M, int N>
   static std::valarray<double> to_valarray(const Eigen::Array<Scalar, M, N>&);
};

template <class Scalar, int M, int N>
std::valarray<double> SingletDM_spectrum_plotter::to_valarray(const Eigen::Array<Scalar, M, N>& v)
{
   return std::valarray<double>(v.data(), v.size());
}

namespace SingletDM_database {

/// append parameter point to database
void to_database(
   const std::string&,
   const SingletDM_mass_eigenstates&,
   const softsusy::QedQcd* qedqcd = 0,
   const Physical_input* physical_input = 0,
   const SingletDM_observables* observables = 0);

/// fill model from an entry of the database
SingletDM_mass_eigenstates from_database(
   const std::string&,
   std::size_t,
   softsusy::QedQcd* qedqcd = 0,
   Physical_input* physical_input = 0,
   SingletDM_observables* observables = 0);

} // namespace SingletDM_database

} // namespace flexiblesusy

#endif
