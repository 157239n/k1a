#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

namespace k1a {

extern PyObject *K1Error;

extern PyMethodDef K1aMethods[];

extern struct PyModuleDef k1amodule;

}  // namespace k1a
