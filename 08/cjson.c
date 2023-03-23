#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>


#include <Python.h>



PyObject *check(PyObject *self, PyObject *args, PyObject *kwargs) {
  PyObject* dict;
  PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict);
  PyObject *key, *value;
  Py_ssize_t pos = 0;
  int count = 0;
  char *str_key;
  char* keys;
  printf("Start....");
  while (PyDict_Next(dict, &pos, &key, &value)) {
    keys += (char*)PyUnicode_AsUTF8(key);
    count++;
  }
  printf("%s", keys);
  Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
    {"check", check, METH_VARARGS, "sum of elements of the list"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef utilsmodule = {PyModuleDef_HEAD_INIT, "cjson", NULL,
                                         -1, methods};

PyMODINIT_FUNC PyInit_cjson(void) { return PyModule_Create(&utilsmodule); }
