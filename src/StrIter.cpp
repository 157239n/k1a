#define PY_SSIZE_T_CLEAN
#include "StrIter.h"

#include <Python.h>

#include <string>

#include "utils.h"

namespace k1a {

void StrIter::init(PyObject *parent) {
    done = false;
    this->parent = parent;
};

std::string StrIter::next() {
    if (debug) log_println("StrIter::next");
    return "";
}

}  // namespace k1a
