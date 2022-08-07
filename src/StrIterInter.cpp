#define PY_SSIZE_T_CLEAN
#include "StrIterInter.h"

#include <Python.h>

#include <string>

#include "utils.h"

namespace k1a {

void StrIterInter::init(PyObject *parent, StrIter og, transformF f) {
    StrIter::init(parent);
    this->f = f;
    this->og = og;
}

PyObject *PyStrIterInter_new(StrIter og, transformF f) {
    PyStrIterInter *parent = PyObject_New(PyStrIterInter, &PyStrIterInter_Type);
    char *fileName;
    if (debug) log_println("StrIterInter_new");
    parent->val.init((PyObject *)parent, og, f);
    return (PyObject *)parent;
}

std::string StrIterInter::next() {
    std::string res = og.next();
    if (og.done) {
        done = true;
        return "";
    } else
        return f(res);
}

PyObject *StrIterInter::Py_repr(PyObject *v) {
    if (debug) log_println("StrIterInter::Py_repr");
    return PyUnicode_FromString("<StrIterInter object>");
}

PyObject *StrIterInter::Py_next(PyObject *self) {
    if (debug) log_println("StrIterInter::Py_next");
    PyStrIterInter *it = (PyStrIterInter *)self;
    std::string res = it->val.next();
    if (it->val.done)
        return NULL;
    else
        return PyUnicode_FromString(res.c_str());
}

void StrIterInter::Py_dealloc(PyObject *self) {
    if (debug) log_println("StrIterInter::Py_dealloc");
    ((PyStrIterInter *)self)->val.del();
    Py_TYPE(self)->tp_free((PyObject *)self);
}

PyTypeObject PyStrIterInter_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0) "StrIterInter",
    sizeof(PyStrIterInter),
    0,
    (destructor)StrIterInter::Py_dealloc, /* tp_dealloc (destructor)str_iter_dealloc */
    0,                                    /* tp_vectorcall_offset */
    0,                                    /* tp_getattr */
    0,                                    /* tp_setattr */
    0,                                    /* tp_as_async */
    (reprfunc)StrIterInter::Py_repr,      /* tp_repr */
    0,                                    /* tp_as_number */
    0,                                    /* tp_as_sequence */
    0,                                    /* tp_as_mapping */
    0,                                    /* tp_hash */
    0,                                    /* tp_call */
    0,                                    /* tp_str */
    PyObject_GenericGetAttr,              /* tp_getattro */
    0,                                    /* tp_setattro */
    0,                                    /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                   /* tp_flags */
    "StrIterInter, intermediate object",  /* tp_doc */
    0,                                    /* tp_traverse */
    0,                                    /* tp_clear */
    0,                                    /* tp_richcompare */
    0,                                    /* tp_weaklistoffset */
    PyObject_SelfIter,                    /* tp_iter */
    (iternextfunc)StrIterInter::Py_next,  /* tp_iternext */
    0,                                    /* tp_methods */
    0,                                    /* tp_members */
    0,                                    /* tp_getset */
    0,                                    /* tp_base */
    0,                                    /* tp_dict */
    0,                                    /* tp_descr_get */
    0,                                    /* tp_descr_set */
    0,                                    /* tp_dictoffset */
    0,                                    /* tp_init */
    PyType_GenericAlloc,                  /* tp_alloc */
    0,                                    /* tp_new */
    PyObject_Del,                         /* tp_free PyObject_Del */
};

}  // namespace k1a
