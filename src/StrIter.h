#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <string>

namespace k1a {

typedef std::string (*transformF)(std::string);

class StrIter {
   private:
    PyObject *parent;

   public:
    bool done;
    void init(PyObject *parent);
    void del(){};
    virtual std::string next();
};

}  // namespace k1a
