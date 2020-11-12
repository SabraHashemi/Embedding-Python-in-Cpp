#include <Python.h>


#include <fstream>

#include <iostream>
#include <sstream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc.hpp>

#include "opencv2/ximgproc.hpp"
using namespace std;

void
main(int argc, char** argv)
{
    // initialize Python
    Py_Initialize();

    // compile our function
    stringstream buf;
    buf << "def add( n1 , n2 ) :" << endl
        << "    return n1+n2" << endl;
    PyObject* pCompiledFn = Py_CompileString(buf.str().c_str(), "", Py_file_input);
    assert(pCompiledFn != NULL);

    // create a module        
    PyObject* pModule = PyImport_ExecCodeModule("test", pCompiledFn);
    assert(pModule != NULL);

    // locate the "add" function (it's an attribute of the module)
    PyObject* pAddFn = PyObject_GetAttrString(pModule, "add");
    assert(pAddFn != NULL);


    // create a new tuple with 2 elements
    PyObject* pPosArgs = PyTuple_New(2);

    // convert the first command-line argument to an int, then put it into the tuple
    PyObject* pVal1 = PyLong_FromString("1", NULL, 10);
    assert(pVal1 != NULL);
    int rc = PyTuple_SetItem(pPosArgs, 0, pVal1); // nb: tuple position 0
    assert(rc == 0);

    // convert the second command-line argument to an int, then put it into the tuple
    PyObject* pVal2 = PyLong_FromString("1000", NULL, 10);
    assert(pVal2 != NULL);
    rc = PyTuple_SetItem(pPosArgs, 1, pVal2); // nb: tuple position 1
    assert(rc == 0);


    // create a new dictionary 
    PyObject* pKywdArgs = PyDict_New();
    assert(pKywdArgs != NULL);

    // call our function 
    PyObject* pResult = PyObject_Call(pAddFn, pPosArgs, pKywdArgs);
    assert(pResult != NULL);


    // convert the result to a string 
    PyObject* pResultRepr = PyObject_Repr(pResult);
    cout << "The answer: " << PyUnicode_AsUTF8(pResultRepr) << endl;





    // clean up
    Py_DecRef(pAddFn);
    Py_DecRef(pModule);
    Py_DecRef(pCompiledFn);
    Py_Finalize();
}
