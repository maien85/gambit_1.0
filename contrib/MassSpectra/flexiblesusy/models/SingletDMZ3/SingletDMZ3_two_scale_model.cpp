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

// File generated at Sat 27 Aug 2016 12:44:59

/**
 * @file SingletDMZ3_two_scale_model.cpp
 * @brief implementation of the SingletDMZ3 model class
 *
 * Contains the definition of the SingletDMZ3 model class methods
 * which solve EWSB and calculate pole masses and mixings from DRbar
 * parameters.
 *
 * This file was generated at Sat 27 Aug 2016 12:44:59 with FlexibleSUSY
 * 1.5.1 (git commit: 8356bacd26e8aecc6635607a32835d534ea3cf01) and SARAH 4.9.0 .
 */

#include "SingletDMZ3_two_scale_model.hpp"

namespace flexiblesusy {

using namespace SingletDMZ3_info;

#define CLASSNAME SingletDMZ3<Two_scale>

CLASSNAME::SingletDMZ3(const SingletDMZ3_input_parameters& input_)
   : Two_scale_model()
   , SingletDMZ3_mass_eigenstates(input_)
{
}

CLASSNAME::~SingletDMZ3()
{
}

void CLASSNAME::calculate_spectrum()
{
   SingletDMZ3_mass_eigenstates::calculate_spectrum();
}

void CLASSNAME::clear_problems()
{
   SingletDMZ3_mass_eigenstates::clear_problems();
}

std::string CLASSNAME::name() const
{
   return SingletDMZ3_mass_eigenstates::name();
}

void CLASSNAME::run_to(double scale, double eps)
{
   SingletDMZ3_mass_eigenstates::run_to(scale, eps);
}

void CLASSNAME::print(std::ostream& out) const
{
   SingletDMZ3_mass_eigenstates::print(out);
}

void CLASSNAME::set_precision(double p)
{
   SingletDMZ3_mass_eigenstates::set_precision(p);
}

std::ostream& operator<<(std::ostream& ostr, const SingletDMZ3<Two_scale>& model)
{
   model.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
