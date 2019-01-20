//                                               -*- C++ -*-
/**
 * @brief JuliaEvaluation implementation
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

#include "JuliaEvaluation.hxx"
// #include <openturns/OSS.hxx"
// #include <openturns/Description.hxx>
// #include <openturns/JuliaWrappingFunctions.hxx>
#include <openturns/PersistentObjectFactory.hxx>
// #include <openturns/Exception.hxx>

using namespace OT;

namespace OTJULIA {

CLASSNAMEINIT(JuliaEvaluation)

static const Factory<JuliaEvaluation> Factory_JuliaEvaluation;



/* Default constructor */
JuliaEvaluation::JuliaEvaluation()
  : EvaluationImplementation()
  , juliaFunction_(nullptr)
//   , pyObj_(NULL)
//   , pyObj_has_exec_(false)
//   , pyObj_has_exec_sample_(false)
//   , pyObj_discard_openturns_memoryview_(true)
//   , pyBufferClass_(NULL)
{
  // Nothing to do
}


/* Constructor from Julia object*/
JuliaEvaluation::JuliaEvaluation(const UnsignedInteger inputDimension,
                                 const UnsignedInteger outputDimension,
                                 jl_function_t * juliaFunction)
  : EvaluationImplementation()
  , inputDimension_(inputDimension)
  , outputDimension_(outputDimension)
  , juliaFunction_(juliaFunction)
//   , pyObj_has_exec_(false)
//   , pyObj_has_exec_sample_(false)
//   , pyObj_discard_openturns_memoryview_(true)
//   , pyBufferClass_(NULL)
{
//   Py_XINCREF(pyCallable);
// 
//   initializeJuliaState();
// 
//   // Set the name of the object as its Julia classname
//   ScopedPyObjectPointer cls(PyObject_GetAttrString (pyObj_,
//                             const_cast<char *>("__class__")));
//   ScopedPyObjectPointer name(PyObject_GetAttrString(cls.get(),
//                              const_cast<char *>("__name__" )));
//   setName(convert< _PyString_, String >(name.get()));
// 
//   const UnsignedInteger inputDimension  = getInputDimension();
//   const UnsignedInteger outputDimension = getOutputDimension();
//   Description description(inputDimension + outputDimension);
// 
//   ScopedPyObjectPointer descIn(PyObject_CallMethod(pyObj_,
//                                const_cast<char *>("getInputDescription"),
//                                const_cast<char *>("()")));
//   if (descIn.get()
//       && PySequence_Check(descIn.get())
//       && (PySequence_Size(descIn.get()) == (SignedInteger)inputDimension))
//   {
//     Description inputDescription(convert< _PySequence_, Description >(descIn.get()));
//     for (UnsignedInteger i = 0; i < inputDimension; ++ i)
//     {
//       description[i] = inputDescription[i];
//     }
//   }
//   else for (UnsignedInteger i = 0; i < inputDimension; ++ i) description[i] = (OSS() << "x" << i);
// 
// 
//   ScopedPyObjectPointer descOut(PyObject_CallMethod(pyObj_,
//                                 const_cast<char *>("getOutputDescription"),
//                                 const_cast<char *>("()")));
//   if (descOut.get()
//       && PySequence_Check(descOut.get())
//       && (PySequence_Size(descOut.get()) == (SignedInteger)outputDimension))
//   {
//     Description outputDescription(convert< _PySequence_, Description >(descOut.get()));
//     for (UnsignedInteger i = 0; i < outputDimension; ++ i)
//     {
//       description[inputDimension + i] = outputDescription[i];
//     }
//   }
//   else for (UnsignedInteger i = 0; i < outputDimension; ++ i) description[inputDimension + i] = (OSS() << "y" << i);
// 
//   setDescription(description);
  setInputDescription(Description::BuildDefault(getInputDimension(), "x"));
  setOutputDescription(Description::BuildDefault(getOutputDimension(), "x"));
}

/* Virtual constructor */
JuliaEvaluation * JuliaEvaluation::clone() const
{
//   Py_XINCREF(pyObj_);
//   Py_XINCREF(pyBufferClass_);
  return new JuliaEvaluation(*this);
}

/* Copy constructor */
// JuliaEvaluation::JuliaEvaluation(const JuliaEvaluation & other)
//   : EvaluationImplementation(other)
//   , juliaFunction_(other.juliaFunction_)
//   , pyBufferClass_(other.pyBufferClass_)
// {
//   Py_XINCREF(pyObj_);
//   Py_XINCREF(pyBufferClass_);
// }

/* Destructor */
// JuliaEvaluation::~JuliaEvaluation()
// {
//   Py_XDECREF(pyObj_);
//   Py_XDECREF(pyBufferClass_);
// }

/* Comparison operator */
Bool JuliaEvaluation::operator ==(const JuliaEvaluation & ) const
{
  return true;
}

/* String converter */
String JuliaEvaluation::__repr__() const
{
  OSS oss;
  oss << "class=" << JuliaEvaluation::GetClassName()
      << " name=" << getName()
      << " description=" << getDescription()
      << " parameter=" << getParameter();
  return oss;
}

/* String converter */
String JuliaEvaluation::__str__(const String & ) const
{
  OSS oss;
  oss << "class=" << JuliaEvaluation::GetClassName()
      << " name=" << getName()
      << " in=" << inputDimension_
      << " out= " << outputDimension_;
  return oss;
}

/* Test for actual implementation */
Bool JuliaEvaluation::isActualImplementation() const
{
  return true;
}



/* Here is the interface that all derived class must implement */

/* Operator () */
Point JuliaEvaluation::operator() (const Point & inP) const
{
  const UnsignedInteger dimension = inP.getDimension();
  if (dimension != getInputDimension())
    throw InvalidDimensionException(HERE) << "Input point has incorrect dimension. Got " << dimension << ". Expected " << getInputDimension();
  auto input_array = jlcxx::ArrayRef<double, 1>(inP.getSize() ? const_cast<double *>(&inP[0]) : 0, inP.getSize());

  callsNumber_.increment();
  jl_value_t * result = juliaFunction_((jl_value_t*)input_array.wrapped());
  if (!result)
    throw InternalException(HERE) << "Julia eval failed";

  jlcxx:: ArrayRef<double, 1> result_array((jl_array_t*)result);
  if (result_array.size() != getOutputDimension())
    throw InvalidDimensionException(HERE) << "Invalid ouput dimension";
  Point outP(outputDimension_);
  std::copy(result_array.begin(), result_array.end(), outP.begin());
  return outP;
}


/* Operator () */
// Sample JuliaEvaluation::operator() (const Sample & inS) const
// {
//   const UnsignedInteger inDim = inS.getDimension();
// 
//   if (inDim != getInputDimension())
//     throw InvalidDimensionException(HERE) << "Sample has incorrect dimension. Got " << inDim << ". Expected " << getInputDimension();
// 
//   const UnsignedInteger size = inS.getSize();
//   const UnsignedInteger outDim = getOutputDimension();
// 
//   Sample outS(0, outDim);
//   if (size > 0)
//   {
//     callsNumber_.fetchAndAdd(size);
// 
//     ScopedPyObjectPointer result;
// 
//     if (pyObj_discard_openturns_memoryview_)
//     {
//       // Force a memory copy of inS into a Julia list
//       ScopedPyObjectPointer inTuple(PyTuple_New(size));
//       for (UnsignedInteger i = 0; i < size; ++ i)
//       {
//         PyObject * eltTuple = PyTuple_New(inDim);
//         for (UnsignedInteger j = 0; j < inDim; ++ j) PyTuple_SetItem(eltTuple, j, convert< Scalar, _PyFloat_ > (inS(i, j)));
//         PyTuple_SetItem(inTuple.get(), i, eltTuple);
//       }
//       ScopedPyObjectPointer execSampleName(convert< String, _PyString_ >("_exec_sample"));
//       result = PyObject_CallMethodObjArgs(pyObj_, execSampleName.get(), inTuple.get(), NULL);
//     }
//     else
//     {
//       // Wrap inS into a memoryview.Buffer object:
//       //    openturns.memoryview.Buffer((int(inS.__baseaddress__()), False), (inS.getSize(), inS.getDimension()))
//       // First argument
//       ScopedPyObjectPointer ptrTuple(PyTuple_New(2));
//       PyTuple_SetItem(ptrTuple.get(), 0, PyLong_FromVoidPtr(static_cast<void *>(const_cast<Scalar*>(inS.__baseaddress__()))));
//       PyTuple_SetItem(ptrTuple.get(), 1, PyBool_FromLong(0));  // We do not own memory
// 
//       // Second argument
//       ScopedPyObjectPointer shapeTuple(PyTuple_New(2));
//       PyTuple_SetItem(shapeTuple.get(), 0, convert< UnsignedInteger, _PyInt_ > (size));
//       PyTuple_SetItem(shapeTuple.get(), 1, convert< UnsignedInteger, _PyInt_ > (inDim));
// 
//       // Call openturns.memoryview.Buffer() to create a read-only buffer
//       ScopedPyObjectPointer readOnlyBufferObj(PyObject_CallObject(pyBufferClass_, Py_BuildValue("OO", ptrTuple.get(), shapeTuple.get())));
// 
//       // Pass this buffer to _exec_sample function if it has been defined by user, otherwise loop on Buffer on call _exec
//       // If both pyObj_has_exec_ and pyObj_has_exec_sample_ are false, this is not a JuliaFunction but a Function(OpenTURNSJuliaFunction).
//       if (pyObj_has_exec_sample_ || ! pyObj_has_exec_)
//       {
//         ScopedPyObjectPointer execSampleName(convert< String, _PyString_ >("_exec_sample"));
//         result = PyObject_CallMethodObjArgs(pyObj_, execSampleName.get(), readOnlyBufferObj.get(), NULL);
//       }
//       else
//       {
//         // Only _exec is defined, not _exec_sample
//         ScopedPyObjectPointer execName(convert< String, _PyString_ >("_exec"));
//         result = PyTuple_New(size);
//         if (execName.get() && result.get())
//         {
//           for(UnsignedInteger i = 0; i < size; ++i)
//           {
//             ScopedPyObjectPointer itemObj(Py_TYPE(readOnlyBufferObj.get())->tp_as_sequence->sq_item(readOnlyBufferObj.get(), i));
//             PyObject * pointI = PyObject_CallMethodObjArgs(pyObj_, execName.get(), itemObj.get(), NULL);
//             if (!pointI)
//             {
//               handleException();
//             }
//             PyTuple_SetItem(result.get(), i, pointI);
//           }
//         }
//       }
//     }
// 
//     if (result.isNull())
//     {
//       handleException();
//     }
// 
//     try
//     {
//       outS = convert< _PySequence_, Sample >(result.get());
//     }
//     catch (InvalidArgumentException &)
//     {
//       throw InvalidArgumentException(HERE) << "Output value for " << getName() << "._exec_sample() method is not a 2d-sequence object";
//     }
//     if (outS.getSize() != size)
//       throw InvalidArgumentException(HERE) << "Julia Function returned a sequence object with incorrect size (got "
//                                            << outS.getSize() << ", expected " << size << ")";
//     if (outS.getDimension() != outDim)
//       throw InvalidArgumentException(HERE) << "Julia Function returned a sequence object with incorrect dimension (got "
//                                            << outS.getDimension() << ", expected " << outDim << ")";
//   }
//   outS.setDescription(getOutputDescription());
//   return outS;
// }

/* Accessor for input point dimension */
void JuliaEvaluation::initializeJuliaState()
{
//   // Check whether JuliaFunction object define these members
//   pyObj_has_exec_ = (PyObject_HasAttrString(pyObj_, "_has_exec") > 0);
//   pyObj_has_exec_sample_ = (PyObject_HasAttrString(pyObj_, "_has_exec_sample") > 0);
//   pyObj_discard_openturns_memoryview_ = (PyObject_HasAttrString(pyObj_, "_discard_openturns_memoryview") > 0);
// 
//   // We do not copy, get a reference to openturns.memoryview.Buffer class
//   if (! pyObj_discard_openturns_memoryview_)
//   {
//     ScopedPyObjectPointer memoryWrapperModule(PyImport_ImportModule("openturns.memoryview"));
//     if (memoryWrapperModule.isNull())
//     {
//       handleException();
//     }
//     pyBufferClass_ = PyObject_GetAttrString(memoryWrapperModule.get(), const_cast<char *>("Buffer"));
//     if (pyBufferClass_ == NULL)
//     {
//       handleException();
//     }
//     Py_INCREF(pyBufferClass_);
//   }
}


/* Accessor for input point dimension */
UnsignedInteger JuliaEvaluation::getInputDimension() const
{
//   ScopedPyObjectPointer result(PyObject_CallMethod (pyObj_,
//                                const_cast<char *>("getInputDimension"),
//                                const_cast<char *>("()")));
//   UnsignedInteger dim = convert< _PyInt_, UnsignedInteger >(result.get());
  return inputDimension_;
}


/* Accessor for output point dimension */
UnsignedInteger JuliaEvaluation::getOutputDimension() const
{
//   ScopedPyObjectPointer result(PyObject_CallMethod (pyObj_,
//                                const_cast<char *>("getOutputDimension"),
//                                const_cast<char *>("()")));
//   UnsignedInteger dim = convert< _PyInt_, UnsignedInteger >(result.get());
  return outputDimension_;
}


/* Method save() stores the object through the StorageManager */
void JuliaEvaluation::save(Advocate & adv) const
{
  EvaluationImplementation::save(adv);

//   pickleSave(adv, pyObj_);
}


/* Method save() reloads the object from the StorageManager */
void JuliaEvaluation::load(Advocate & adv)
{
  EvaluationImplementation::load(adv);

//   pickleLoad(adv, pyObj_);
//   initializeJuliaState();
}


}
