#include <Python.h>

#include <stdbool.h>

#include <stdio.h>

#include <stdlib.h>

/*PyObject *dump(PyObject *self, PyObject *args, PyObject *kwargs) {
  PyObject *dict;
  PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict);
  Py_RETURN_NONE;
}
*/

PyObject * load(PyObject *self, PyObject *args, PyObject *kwargs) {
        PyObject *dict = NULL;
        PyObject *key = NULL;
        PyObject *value = NULL;
        int val;
        if (!(dict = PyDict_New())) {
                printf("ERROR: Failed to create Dict Object\n");
                return NULL;
        }
        char *string;
        char *token;
        char *_key;
        char _value[100];
        if (!PyArg_ParseTuple(args, "s", &string)) {
                PyErr_SetString(PyExc_TypeError, "Parameter must be a string!");
                return NULL;
        }
        token = strtok(string, "{\",: }");
        while (token != NULL) {
                _key = token;
                token = strtok(NULL, "{\",: }");
                strcpy(_value, token);
                if (!(key = Py_BuildValue("s", _key))) {
                        printf("ERROR: Failed to build string value\n");
                        return NULL;
                }
                char *endptr;
                strtol(_value, &endptr, 10);
                if ( *endptr == '\0') {
                        int val = atoi(_value);
                        if (!(value = Py_BuildValue("i", val))) {
                                printf("ERROR: Failed to build integer value\n");
                                return NULL;
                        }
                } else {
                        if (!(value = Py_BuildValue("s", _value))) {
                                printf("ERROR: Failed to build integer value\n");
                                return NULL;
                        }
                }
                if (PyDict_SetItem(dict, key, value) < 0) {
                        printf("ERROR: Failed to set item\n");
                        return NULL;
                }
                token = strtok(NULL, "{\",: }");
        }
        return dict;
}

static PyMethodDef methods[] = {
        {
                "load",
                load,
                METH_VARARGS,
                "load json"
        },
        {
                NULL,
                NULL,
                0,
                NULL
        }
};

static struct PyModuleDef utilsmodule = {
        PyModuleDef_HEAD_INIT,
        "cjson",
        NULL,
        -1,
        methods
};

PyMODINIT_FUNC PyInit_cjson(void) {
        return PyModule_Create( &utilsmodule);
}