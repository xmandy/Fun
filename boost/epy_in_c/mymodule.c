#include <Python.h>


static PyObject*
my_show(PyObject *self, PyObject *args)
{
    return PyString_FromString("just a test!");
}

static PyMethodDef my_methods[] = {
    {"show", my_show, METH_NOARGS, "show a test string"},
    {NULL, NULL}
};

PyMODINIT_FUNC
initmy(void)
{
    PyObject *m;
    m = Py_InitModule("my", my_methods);
}
