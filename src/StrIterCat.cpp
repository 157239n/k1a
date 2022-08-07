#define PY_SSIZE_T_CLEAN
#include "StrIterCat.h"

#include <Python.h>
#include <structmember.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"

namespace k1a {

void StrIterCat::init(PyObject *parent, std::string fileName) {
    StrIter::init(parent);
    this->fileName = new std::string(fileName);
    this->fp = new std::ifstream(fileName);
};

void StrIterCat::del() {
    StrIter::del();
    fp->close();
    delete fileName;
    if (debug) log_println("destroyed");
}

std::string StrIterCat::next() {
    if (debug) log_println("StrIterCat::next");
    std::string line;
    if (std::getline(*fp, line))
        return line;
    else {
        done = true;
        return "";
    }
};

PyObject *StrIterCat::Py_repr(PyObject *v) {
    if (debug) log_println("StrIterCat::Py_repr");
    return PyUnicode_FromString("inside repr");
}

PyObject *PyStrIterCat_new(std::string fileName) {
    if (debug) log_println("PyStrIterCat_new");
    PyStrIterCat *res = PyObject_New(PyStrIterCat, &PyStrIterCat_Type);
    res->val.init((PyObject *)res, fileName);
    return (PyObject *)res;
}

PyObject *PyStrIterCat_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyStrIterCat *return_value = PyObject_New(PyStrIterCat, type);
    char *fileName;
    PyArg_ParseTuple(args, "s", &fileName);
    return PyStrIterCat_new(std::string(fileName));
}

PyObject *StrIterCat::Py_next(PyObject *self) {
    PyStrIterCat *it = (PyStrIterCat *)self;
    if (debug) log_println("StrIterCat::Py_next");
    std::string res = it->val.next();
    if (it->val.done)
        return NULL;
    else
        return PyUnicode_FromString(res.c_str());
}

void StrIterCat::Py_dealloc(PyObject *self) {
    PyStrIterCat *_self = (PyStrIterCat *)self;
    if (debug) log_println("StrIterCat::Py_dealloc");
    _self->val.del();
    Py_TYPE(_self)->tp_free((PyObject *)_self);
}

PyTypeObject PyStrIterCat_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0) "StrIterCat",
    sizeof(PyStrIterCat),
    0,
    (destructor)StrIterCat::Py_dealloc, /* tp_dealloc (destructor)str_iter_dealloc */
    0,                                  /* tp_vectorcall_offset */
    0,                                  /* tp_getattr */
    0,                                  /* tp_setattr */
    0,                                  /* tp_as_async */
    (reprfunc)StrIterCat::Py_repr,      /* tp_repr */
    0,                                  /* tp_as_number */
    0,                                  /* tp_as_sequence */
    0,                                  /* tp_as_mapping */
    0,                                  /* tp_hash */
    0,                                  /* tp_call */
    0,                                  /* tp_str */
    PyObject_GenericGetAttr,            /* tp_getattro */
    0,                                  /* tp_setattro */
    0,                                  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "some str_iter_doc docs",           /* tp_doc */
    0,                                  /* tp_traverse */
    0,                                  /* tp_clear */
    0,                                  /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    PyObject_SelfIter,                  /* tp_iter */
    (iternextfunc)StrIterCat::Py_next,  /* tp_iternext */
    PyStrIterCat_methods,               /* tp_methods */
    0,                                  /* tp_members */
    0,                                  /* tp_getset */
    0,                                  /* tp_base */
    0,                                  /* tp_dict */
    0,                                  /* tp_descr_get */
    0,                                  /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    0,                                  /* tp_init */
    PyType_GenericAlloc,                /* tp_alloc */
    PyStrIterCat_new,                   /* tp_new */
    PyObject_Del,                       /* tp_free PyObject_Del */
};

}  // namespace k1a
