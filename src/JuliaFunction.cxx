//                                               -*- C++ -*-
/**
 *  @brief The class that implements analytical functions.
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

#include <openturns/CenteredFiniteDifferenceGradient.hxx>
#include <openturns/CenteredFiniteDifferenceHessian.hxx>

#include "JuliaFunction.hxx"
#include "JuliaEvaluation.hxx"

using namespace OT;

namespace OTJULIA {

CLASSNAMEINIT(JuliaFunction)

/* Default constructor */
JuliaFunction::JuliaFunction ()
  : Function()
{
  // Nothing to do
}


/* Parameter constructor */
JuliaFunction::JuliaFunction (const UnsignedInteger inputDimension,
                  const UnsignedInteger outputDimension,
                  jl_function_t* juliaFunction)
  : Function()
{
// #ifdef OPENTURNS_HAVE_ANALYTICAL_PARSER
//   const Description outputVariablesNames(Description::BuildDefault(formulas.getSize(), "y"));
// 
//   // Try to build an analytical gradient
  JuliaEvaluation evaluation(inputDimension, outputDimension, juliaFunction);
  setEvaluation(evaluation.clone());
//   try
//   {
//     setGradient(new SymbolicGradient(evaluation));
//   }
//   catch(...)
  {
//     LOGWARN("Cannot compute an analytical gradient, using finite differences instead.");
    const Scalar epsilon = ResourceMap::GetAsScalar("CenteredFiniteDifferenceGradient-DefaultEpsilon");
    setGradient(new CenteredFiniteDifferenceGradient(epsilon, getEvaluation()));
  }
//   try
//   {
//     setHessian(new SymbolicHessian(evaluation));
//   }
//   catch(...)
  {
//     LOGWARN("Cannot compute an analytical hessian, using finite differences instead.");
    const Scalar epsilon = ResourceMap::GetAsScalar("CenteredFiniteDifferenceHessian-DefaultEpsilon");
    setHessian(new CenteredFiniteDifferenceHessian(epsilon, getEvaluation()));
  }
// #else
//   throw NotYetImplementedException(HERE) << "JuliaFunction requires muParser or ExprTk";
// #endif
}

/* String converter */
String JuliaFunction::__repr__() const
{
  OSS oss;
  oss << "class=" << JuliaFunction::GetClassName()
      << " name=" << getName()
      << " implementation=" << getImplementation()->__repr__();
  return oss;
}

String JuliaFunction::__str__(const String & offset) const
{
  return getImplementation()->__str__(offset);
}

}

