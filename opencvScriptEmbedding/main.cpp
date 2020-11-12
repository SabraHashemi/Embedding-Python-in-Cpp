#include <Python.h>


#include <fstream>

#include <iostream>
#include <sstream>

#include "numpy/arrayobject.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc.hpp>

//# include <opencv2/dirent.h>

#include "opencv2/ximgproc.hpp"

//#include "module.hpp"
#include "opencv2/core/types_c.h"
#include "opencv2/opencv_modules.hpp"
#include "D:\opencv-4.2.0\opencv-4.2.0\modules\python\src2\\pycompat.hpp"





#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

using namespace std;


PyObject* pName;
int  main(int argc, char** argv)
{
    // initialize Python
    Py_Initialize();

    //PyRun_SimpleString("from time import time,ctime\n"
    //    "print('Today is',ctime(time()))\n");
    ////Run a simple file
    //FILE* PScriptFile = fopen("OCD/newbefore.py", "r");
    //if (PScriptFile) {
    //    PyRun_SimpleFile(PScriptFile, "OCD/newbefore.py");
    //    fclose(PScriptFile);
    //}


    cv::Mat img = cv::imread("C:\\1.jpg");

    // compile our function

string script= R""""(

"""  
Copyright (c) 2019-present NAVER Corp.
MIT License
"""

# -*- coding: utf-8 -*-
import time
# -*- coding: utf-8 -*-
import sys
import os
import time
import argparse

import torch
print(torch.__path__)
print("hereeeeeee in new before ")
print(torch.__version__)
print(torch.__path__)
import torch.nn as nn
import torch.backends.cudnn as cudnn
from torch.autograd import Variable

from PIL import Image

import cv2
from skimage import io
import numpy as np
sys.path.append('OCD/')
import craft_utils
import imgproc
import file_utils
import json
import zipfile

from craft import CRAFT

from collections import OrderedDict


def saveResult(img):

            finalImage,  = np.array(img)
            print(finalImage, .shape)
            blur = cv2.GaussianBlur(cv2.cvtColor(finalImage, cv2.COLOR_RGB2GRAY), (5, 5), 0)
            ret2, th2 = cv2.threshold(blur, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
            cv2.imshow("plate_thresh", th2)
            cv2.waitKey(1)
            return bytearray(finalImage)



def load_data2(inputimage):
    
    image = inputimage
    imm=saveResult(image, polys, score_text, dirname=result_folder)
    return imm





)"""";


    PyObject* pCompiledFn = Py_CompileString(script.c_str(), "", Py_file_input);
    assert(pCompiledFn != NULL);


    // create a module        
    PyObject* pModule = PyImport_ExecCodeModule("test", pCompiledFn);
    assert(pModule != NULL);

    if (pModule == NULL)
    {
        PyErr_Print();
        return 0;
    }



    // locate the "our" function (it's an attribute of the module)
    PyObject* pAddFn = PyObject_GetAttrString(pModule, "workOnMat");
    assert(pAddFn != NULL);
    if (pAddFn == NULL)
    {
        PyErr_Print();
        return 0;
    }

    // create a new tuple with 2 elements
    PyObject* pPosArgs = PyTuple_New(1);

    // convert the first command-line argument to an int, then put it into the tuple
    import_array();
    npy_intp dimensions[3] = { img.rows, img.cols, img.channels() };
    PyObject*  pVal1 = PyArray_SimpleNewFromData(img.dims + 1, (npy_intp*)&dimensions, NPY_UINT8, img.data);
    int rc = PyTuple_SetItem(pPosArgs, 0, pVal1); // nb: tuple position 0
    assert(rc == 0);


    // create a new dictionary 
    PyObject* pKywdArgs = PyDict_New();
    assert(pKywdArgs != NULL);
    if (pKywdArgs == NULL)
    {
        PyErr_Print();
        return 0;
    }
    // call our function 
    PyObject* pResult = PyObject_Call(pAddFn, pPosArgs, pKywdArgs);
    assert(pResult != NULL);
    if (pResult == NULL)
    {
        PyErr_Print();
        return 0;
    }



    uchar* data = (uchar*)PyByteArray_AsString(pResult);
    cv::Mat imgg(100, 350, CV_8UC3, data);
    imshow("imgg", imgg);
    cv::waitKey(0);

//below code dosn't work for me, i dont konw that its correct or not

    //PyArrayObject* contig = (PyArrayObject*)PyArray_FromAny(pResult,
    //    PyArray_DescrFromType(NPY_UINT8),
    //    0, 0, NPY_ARRAY_CARRAY, NULL);
    //assert(contig && PyArray_DIM(contig, 2) == 3);
    //if (contig == nullptr) {
    //    // Throw an exception
    //    PyErr_Print();
    //    return 0;
    //}

    //cv::Mat mat(PyArray_DIM(contig, 0), PyArray_DIM(contig, 1), CV_8UC3,
    //    PyArray_DATA(contig));

    //imshow("mat", mat);
    //cv::waitKey(0);
   





    // clean up
    Py_DecRef(pAddFn);
    Py_DecRef(pModule);
    Py_DecRef(pCompiledFn);
    Py_Finalize();

    return 0;
};