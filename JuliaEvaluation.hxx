//                                               -*- C++ -*-
/**
 * @brief JuliaEvaluation declaration
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

#ifndef OPENTURNS_JULIAEVALUATION_HXX
#define OPENTURNS_JULIAEVALUATION_HXX

#include <jlcxx/functions.hpp>
#include <openturns/EvaluationImplementation.hxx>



namespace OTJULIA {

/**
 * @class JuliaEvaluation
 *
 * This class binds a Julia function to an OpenTURNS' Function
 */
class JuliaEvaluation
  : public OT::EvaluationImplementation
{
  CLASSNAME
public:


  /** Constructor from Julia object*/
  JuliaEvaluation(const OT::UnsignedInteger inputDimension,
                  const OT::UnsignedInteger outputDimension,
                  jl_function_t* juliaFunction);

  /** Copy constructor */
//   JuliaEvaluation(const JuliaEvaluation & other);

  /** Virtual constructor */
  virtual JuliaEvaluation * clone() const;

  /** Destructor */
//   virtual ~JuliaEvaluation();

  /** Comparison operator */
  OT::Bool operator ==(const JuliaEvaluation & other) const;

  /** String converter */
  virtual OT::String __repr__() const;
  virtual OT::String __str__(const OT::String & offset) const;


  /** Test for actual implementation */
  virtual OT::Bool isActualImplementation() const;


  /* Here is the interface that all derived class must implement */

  /** Operator () */
  virtual OT::Point operator() (const OT::Point & inP) const;

//   virtual Sample operator() (const Sample & inS) const;

  /** Accessor for input point dimension */
  virtual OT::UnsignedInteger getInputDimension() const;

  /** Accessor for output point dimension */
  virtual OT::UnsignedInteger getOutputDimension() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(OT::Advocate & adv) const;

  /** Method save() reloads the object from the StorageManager */
  virtual void load(OT::Advocate & adv);

protected:


private:

  friend class OT::Factory<JuliaEvaluation>;

  /** Default constructor */
  JuliaEvaluation();

  /** Set pyBufferClass_ and pyObj_*_ members */
  void initializeJuliaState();

  OT::UnsignedInteger inputDimension_;
  OT::UnsignedInteger outputDimension_;
  
  /** The underlying Julia function */
//   jl_function_t* juliaFunction_;
  jlcxx::JuliaFunction juliaFunction_;
//   PyObject * pyObj_;
// 
//   /** Tell whether Julia callable object define these members */
//   Bool pyObj_has_exec_;
//   Bool pyObj_has_exec_sample_;
//   Bool pyObj_discard_openturns_memoryview_;

  /** Julia openturns.memoryview.Buffer class */
//   PyObject * pyBufferClass_;

}; /* class JuliaEvaluation */


}

#endif /* OPENTURNS_JULIAEVALUATION_HXX */

