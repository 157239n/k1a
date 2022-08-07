#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "StrIterCat.h"
#include "funcs.h"
#include "utils.h"

extern "C" {
PyMODINIT_FUNC PyInit_k1a(void) {
    PyObject *m;

    if (k1a::debug) {
        k1a::log_clear();
        k1a::log_println("module init");
    }

    m = PyModule_Create(&k1a::k1amodule);
    if (m == NULL) return NULL;

    // k1a::K1Error = PyErr_NewException("k1a.error", NULL, NULL);
    Py_XINCREF(k1a::K1Error);
    PyModule_AddObject(m, "error", k1a::K1Error);

    char *version = "1.1";
    PyModule_AddObject(m, "__version__", PyUnicode_FromString(version));

    Py_INCREF(&k1a::PyStrIterCat_Type);
    PyModule_AddObject(m, "str_iter", (PyObject *)&k1a::PyStrIterCat_Type);

    if (k1a::debug) k1a::log_println("module finish init");
    return m;
}
}
