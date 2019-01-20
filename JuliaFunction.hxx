//                                               -*- C++ -*-
/**
 *  @brief The class that implements symbolic functions.
 *
 *  Copyright 2005-2018 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef OPENTURNS_JULIAFUNCTION_HXX
#define OPENTURNS_JULIAFUNCTION_HXX

#include <julia/julia.h>

#include <openturns/Function.hxx>


namespace OTJULIA {


/**
 * @class JuliaFunction
 *
 */
class OT_API JuliaFunction
  : public OT::Function
{
  CLASSNAME
public:

  /* Default constructor */
  JuliaFunction();

  /** Parameter constructor */
  JuliaFunction (const OT::UnsignedInteger inputDimension,
                const OT::UnsignedInteger outputDimension,
                jl_function_t* juliaFunction);

  /** String converter */
  virtual OT::String __repr__() const;
  virtual OT::String __str__(const OT::String & offset = "") const;


private:

}; /* class QuadraticFunction */


}

#endif /* OPENTURNS_JULIAFUNCTION_HXX */
