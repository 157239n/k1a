/**
 * @file funcs.cpp
 * @brief Independent functions
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <string>

#include "StrIterCat.h"
#include "StrIterInter.h"
#include "utils.h"

namespace k1a {

PyObject *K1Error = PyErr_NewException("k1a.error", NULL, NULL);

PyObject *k1a_system(PyObject *self, PyObject *args) {
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command)) return NULL;
    sts = system(command);
    if (sts < 0) {
        PyErr_SetString(K1Error, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

PyObject *k1a_test(PyObject *self, PyObject *args) {
    const char *str;
    if (!PyArg_ParseTuple(args, "s", &str)) return NULL;
    const std::string a = str;
    auto b = (PyStrIterCat *)PyStrIterCat_new(a);
    return PyStrIterInter_new(b->val, [](std::string x) { return x + "|end"; });
    // return;
    //  return PyUnicode_FromString("def");
    //  return PyUnicode_FromString((a + "end").c_str());
}

PyObject *k1a_str_split(PyObject *self, PyObject *args) {
    char *_str, *_delim, *str, *begin;
    if (!PyArg_ParseTuple(args, "ss", &_str, &_delim)) return NULL;
    char delim = _delim[0], quoteChar = '"';

    begin = str = (char *)malloc((strlen(_str) + 1) * sizeof(char));
    strcpy(str, _str);
    PyObject *plist = PyList_New(0);

    int i = 0;
    bool inBlock = false;

    while (str[i] != NULL) {
        char a = str[i];
        if (a == delim && !inBlock) {
            str[i] = NULL;
            PyList_Append(plist, PyUnicode_FromString(begin));
            begin = str + (i + 1);
        } else if (!inBlock && (a == '"' || a == '\'')) {  // new block
            inBlock = true;
            quoteChar = a;
        } else if (inBlock && a == quoteChar)
            inBlock = false;  // exiting block
        i++;
    }
    PyList_Append(plist, PyUnicode_FromString(begin));
    free(str);
    return plist;
}

PyMethodDef K1aMethods[] = {
    {"system", k1a_system, METH_VARARGS, "Execute a shell command."},
    {"test", k1a_test, METH_VARARGS,
     "Test function for developing the library"},
    {"clear", k1a_log_clear, METH_VARARGS, "Clear logs"},
    {"str_split", k1a_str_split, METH_VARARGS,
     "Splits string into multiple fragments using a delimiter, respecting "
     "quotes"},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

struct PyModuleDef k1amodule = {
    PyModuleDef_HEAD_INIT, "k1a", /* name of module */
    NULL,                         /* module documentation, may be NULL */
    -1,                           /* size of per-interpreter state of the module,
                                     or -1 if the module keeps state in global variables. */
    K1aMethods};

}  // namespace k1a
