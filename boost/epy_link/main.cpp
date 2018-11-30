#include <Python.h>

extern "C" void initmy();

int main(int argc, char const *argv[])
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

    if (argc < 3) {
        fprintf(stderr, "Usage: call [python-file] [func-name] [args]\n");
        return 1;
    }

    Py_Initialize();

    // Must set sys path before import module, or you will get error output:
    // ImportError : no module xxx
    PyObject *py_sys = PyImport_ImportModule("sys");
    PyObject *py_sys_dict = PyModule_GetDict(py_sys);
    PyObject *py_path = PyDict_GetItemString(py_sys_dict, "path");
    PyList_Insert(py_path, 0, PyString_FromString("."));

    initmy();


    pName = PyString_FromString(argv[1]);

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL)
    {
        pFunc = PyObject_GetAttrString(pModule, argv[2]);

        if (pFunc && PyCallable_Check(pFunc))
        {
            pArgs = PyTuple_New(argc - 3);
            for (i = 0 ; i < argc - 3; ++i)
            {
                pValue = PyInt_FromLong(atoi(argv[i+3]));
                if (!pValue)
                {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot Convert argument!\n");
                    return 1;
                }
                PyTuple_SetItem(pArgs, i, pValue);
            }

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL)
            {
                printf("Result of call: %ld\n", PyInt_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr, "Call failed!\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();

            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }

        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load module: %s\n", argv[1]);
        return 1;
    }

    Py_Finalize();

    return 0;
}


