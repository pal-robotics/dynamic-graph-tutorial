/*
 *  Copyright 2010 CNRS
 *
 *  Florent Lamiraux
 */

#include <Python.h>
#include "dynamic-graph/tutorial/inverted-pendulum.hh"

using dynamicgraph::tutorial::InvertedPendulum;

namespace invertedPendulum {

  static void destroy (void* self);
  static PyObject* error;

  /**
     \brief Create an instance of InvertedPendulum
  */
  static PyObject*
  create(PyObject* self, PyObject* args)
  {
    char *name = NULL;

    if (!PyArg_ParseTuple(args, "s", &name))
      return NULL;

    InvertedPendulum* obj = NULL;
    try {
      obj = new InvertedPendulum(std::string(name));
    } catch (dynamicgraph::ExceptionFactory& exc) {
      PyErr_SetString(error, exc.getStringMessage().c_str());
      return NULL;
    }

    // Return the pointer as an integer
    return PyCObject_FromVoidPtr((void*)obj, destroy);
  }

  /**
     \brief Destroy an instance of InvertedPendulum
  */
  static void
  destroy (void* self)
  {
    InvertedPendulum* obj = (InvertedPendulum*)self;
    delete obj;
  }

  /**
     \brief Binding for InvertedPendulum::getCartMass
  */
  static PyObject*
  getCartMass (PyObject* self, PyObject* args)
  {
    InvertedPendulum* obj = NULL;
    unsigned int pointer;

    if (!PyArg_ParseTuple(args, "O", &pointer))
      return NULL;

    obj = (InvertedPendulum*)pointer;
    double result = obj->getCartMass();

    return Py_BuildValue("f", result);
  }

  /**
     \brief Binding for InvertedPendulum::setCartMass
  */
  static PyObject*
  setCartMass (PyObject* self, PyObject* args)
  {
    InvertedPendulum* obj = NULL;
    void* pointer;
    double value;

    if (!PyArg_ParseTuple(args, "Od", &pointer, &value))
      return NULL;

    obj = (InvertedPendulum*)pointer;
    obj->setCartMass(value);

    return Py_BuildValue("");
  }

  /**
     \brief Binding for InvertedPendulum::getPendulumMass
  */
  static PyObject*
  getPendulumMass (PyObject* self, PyObject* args)
  {
    InvertedPendulum* obj = NULL;
    void* pointer;

    if (!PyArg_ParseTuple(args, "O", &pointer))
      return NULL;

    obj = (InvertedPendulum*)pointer;
    double result = obj->getPendulumMass();

    return Py_BuildValue("f", result);
  }

  /**
     \brief Binding for InvertedPendulum::setPendulumMass
  */
  static PyObject*
  setPendulumMass (PyObject* self, PyObject* args)
  {
    InvertedPendulum* obj = NULL;
    void* pointer;
    double value;

    if (!PyArg_ParseTuple(args, "Od", &pointer, &value))
      return NULL;

    obj = (InvertedPendulum*)pointer;
    obj->setPendulumMass(value);

    return Py_BuildValue("");
  }
}

/**
   \brief List of python functions
*/
static PyMethodDef dynamicGraphTutorialMethods[] = {
  {"createInvertedPendulum",  invertedPendulum::create, METH_VARARGS,
     "Create an instance of InvertedPendulum."},
  {"invertedPendulumGetCartMass", invertedPendulum::getCartMass, METH_VARARGS,
   "Get mass of the cart of inverted pendulum."},
  {"invertedPendulumSetCartMass", invertedPendulum::setCartMass, METH_VARARGS,
   "Set mass of the cart of inverted pendulum."},
  {"invertedPendulumGetPendulumMass", invertedPendulum::getPendulumMass,
   METH_VARARGS, "Get mass of the pendulum."},
  {"invertedPendulumSetPendulumMass", invertedPendulum::setPendulumMass,
   METH_VARARGS, "Set mass of the pendulum."},
  {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initwrap(void)
{
    PyObject *m;

    m = Py_InitModule("wrap", dynamicGraphTutorialMethods);
    if (m == NULL)
        return;

    invertedPendulum::error =
      PyErr_NewException("dynamic_graph.tutorial.wrap.error",
			 NULL, NULL);
    Py_INCREF(invertedPendulum::error);
    PyModule_AddObject(m, "error", invertedPendulum::error);
}