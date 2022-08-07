#include "utils.h"

#include <fstream>
#include <iostream>
#include <string>

namespace k1a {

bool debug = true;

void log_clear() {
    std::ofstream f;
    f.open("/home/kelvin/repos/labs/k1a/logs.txt");
    f << "";
    f.close();
}

PyObject *k1a_log_clear(PyObject *self, PyObject *args) {
    log_clear();
    Py_RETURN_NONE;
}

}  // namespace k1a
