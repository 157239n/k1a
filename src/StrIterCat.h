#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "StrIter.h"

namespace k1a {

class StrIterCat : public StrIter {
   public:
    std::string *fileName;
    void init(PyObject *parent, std::string fileName);
    void del();
    std::string next();
    static PyObject *Py_repr(PyObject *);
    static PyObject *Py_next(PyObject *);
    static void Py_dealloc(PyObject *);

   private:
    std::ifstream *fp;
};

typedef struct {
    PyObject_HEAD;
    StrIterCat val;
} PyStrIterCat;

static PyObject *str_iter_conjugate(PyStrIterCat *self,
                                    PyObject *Py_UNUSED(ignored)) {
    return PyUnicode_FromString("str_iter_conjugate");
};

static PyMethodDef PyStrIterCat_methods[] = {
    {"conjugate", (PyCFunction)str_iter_conjugate, METH_NOARGS,
     "conjugate docs"},
    {NULL, NULL}};

PyObject *PyStrIterCat_new(std::string fileName);
PyObject *PyStrIterCat_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);
extern PyTypeObject PyStrIterCat_Type;

}  // namespace k1a
