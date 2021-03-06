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

// File generated at Sat 27 Aug 2016 12:40:27

#ifndef SSM_TWO_SCALE_SUSY_SCALE_CONSTRAINT_H
#define SSM_TWO_SCALE_SUSY_SCALE_CONSTRAINT_H

#include "SSM_susy_scale_constraint.hpp"
#include "SSM_input_parameters.hpp"
#include "two_scale_constraint.hpp"
#include "lowe.h"

namespace flexiblesusy {

template <class T>
class SSM;

class Two_scale;

template<>
class SSM_susy_scale_constraint<Two_scale> : public Constraint<Two_scale> {
public:
   SSM_susy_scale_constraint();
   SSM_susy_scale_constraint(SSM<Two_scale>*, const softsusy::QedQcd&);
   virtual ~SSM_susy_scale_constraint();
   virtual void apply();
   virtual double get_scale() const;
   virtual void set_model(Two_scale_model*);

   void clear();
   double get_initial_scale_guess() const;
   const SSM_input_parameters& get_input_parameters() const;
   SSM<Two_scale>* get_model() const;
   void initialize();
   const softsusy::QedQcd& get_sm_parameters() const;
   void set_sm_parameters(const softsusy::QedQcd&);

protected:
   void update_scale();

private:
   double scale;
   double initial_scale_guess;
   SSM<Two_scale>* model;
   softsusy::QedQcd qedqcd;
};

} // namespace flexiblesusy

#endif
