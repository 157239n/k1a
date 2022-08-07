#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <string>

#include "StrIter.h"

namespace k1a {

/**
 * @brief Intermediate string iterator
 *
 */
class StrIterInter : public StrIter {
   private:
    transformF f;
    StrIter og;

   public:
    void init(PyObject *parent, StrIter og, transformF f);
    std::string next();
    static PyObject *Py_next(PyObject *self);
    static void Py_dealloc(PyObject *self);
    static PyObject *Py_repr(PyObject *self);
};

typedef struct {
    PyObject_HEAD;
    StrIterInter val;
} PyStrIterInter;

PyObject *PyStrIterInter_new(StrIter og, transformF f);

extern PyTypeObject PyStrIterInter_Type;

}  // namespace k1a
