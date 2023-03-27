#include <Python.h>

#include <stdbool.h>

#include <stdio.h>

#include <stdlib.h>

char* add(const char *s1, const char *s2)
{
    char *char_r = malloc(strlen(s1) + strlen(s2) + 1); // +1 last '\0'
    strcpy(char_r, s1);
    strcat(char_r, s2);
    return char_r;
}
char* int2char(int number) {
    char* buffer = malloc(sizeof(char) * 10);
    sprintf(buffer, "%d", number);
    return buffer;
}


PyObject* dumps(PyObject *self, PyObject *args, PyObject *kwargs) {
        PyObject *dict = NULL, *key = NULL, *value = NULL;
        size_t last = 0;
        if (!PyArg_ParseTuple(args, "O", &dict))
        {
                printf("Args must be dict!");
                return NULL;
        }
        char* str_res = "{";
        Py_ssize_t pos = 0;
        while(PyDict_Next(dict, &pos, &key, &value))
        {
                char* _key = PyUnicode_AsUTF8(key);
                if(last != 0 ){
                        _key = add(", \"", _key);
                }
                else{
                        _key = add("\"", _key);

                }
                _key = add(_key, "\": ");
                str_res = add(str_res, _key);
                char* _value = NULL;
                if(!PyLong_Check(value)){
                        _value = PyUnicode_AsUTF8(value);
                        _value = add("\"", _value);
                        _value = add(_value, "\"");
                        str_res = add(str_res, _value);
                }
                else{
                        int _value_int = PyLong_AsLong(value);
                        _value = int2char(_value_int);
                        str_res = add(str_res, _value);
                        free(_value);
                }
                last++;
        }
        str_res = add(str_res, "}");
        return Py_BuildValue("s", str_res);
}


PyObject *loads(PyObject *self, PyObject *args, PyObject *kwargs) {
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
                loads,
                METH_VARARGS,
                "load json"
        },
        {
                "dumps",
                dumps,
                METH_VARARGS,
                "dump json"
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