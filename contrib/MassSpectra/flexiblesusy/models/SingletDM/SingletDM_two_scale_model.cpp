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

// File generated at Sat 27 Aug 2016 12:44:12

/**
 * @file SingletDM_two_scale_model.cpp
 * @brief implementation of the SingletDM model class
 *
 * Contains the definition of the SingletDM model class methods
 * which solve EWSB and calculate pole masses and mixings from DRbar
 * parameters.
 *
 * This file was generated at Sat 27 Aug 2016 12:44:12 with FlexibleSUSY
 * 1.5.1 (git commit: 8356bacd26e8aecc6635607a32835d534ea3cf01) and SARAH 4.9.0 .
 */

#include "SingletDM_two_scale_model.hpp"

namespace flexiblesusy {

using namespace SingletDM_info;

#define CLASSNAME SingletDM<Two_scale>

CLASSNAME::SingletDM(const SingletDM_input_parameters& input_)
   : Two_scale_model()
   , SingletDM_mass_eigenstates(input_)
{
}

CLASSNAME::~SingletDM()
{
}

void CLASSNAME::calculate_spectrum()
{
   SingletDM_mass_eigenstates::calculate_spectrum();
}

void CLASSNAME::clear_problems()
{
   SingletDM_mass_eigenstates::clear_problems();
}

std::string CLASSNAME::name() const
{
   return SingletDM_mass_eigenstates::name();
}

void CLASSNAME::run_to(double scale, double eps)
{
   SingletDM_mass_eigenstates::run_to(scale, eps);
}

void CLASSNAME::print(std::ostream& out) const
{
   SingletDM_mass_eigenstates::print(out);
}

void CLASSNAME::set_precision(double p)
{
   SingletDM_mass_eigenstates::set_precision(p);
}

std::ostream& operator<<(std::ostream& ostr, const SingletDM<Two_scale>& model)
{
   model.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
