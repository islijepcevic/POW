/*
 * PSO.i
 *
 * this is the SWIG module file which links c++ module to python
 *
 * Author: Ivan Slijepcevic, ivan.slijepcevic@epfl.ch
 */
%module(directors="1") PSO

%{
#define SWIG_FILE_WITH_INIT
#include "PSO.hpp"
%}

// DIRECTORS - they enable inheritance and polymorphism from c++ to python
%feature("director") AbstractFitness;
%feature("director") BaseParameters;

// INCLUSION OF ALL THE FILES/CLASESS IMPLEMENTED IN C++
// this is instead of rewriting all the code here
%include "BaseParameters.hpp"
%include "AbstractSpace.hpp"
%include "PSO.hpp"

// THE FOLLOWING CODE SERVES AS INTERFACE BETWEEN C++ AND PYTHON DATA STRUCTURES

// these functions are to be used for C/C++ structures
%inline %{

/*
 * make new dynamically allocated C-like array
 * @param size - size of the array
 * @return - the pointer to the new array
 */
double *swigNewCArray(int size) {
    double *array = new double[size];
    return array;
}

/*
 * get the element of C-like array;
 * WARNING: no check will be performed for the array boundaries
 * @param a - the pointer to the array
 * @param index - index of the wanted element
 * @return - wanted element
 */
double swigCArrayGet(double* a, int index) {
    return a[index];
}

/*
 * set the element of C-like array;
 * WARNING: no check will be performed for the array boundaries
 * @param a - the pointer to the array
 * @param index - index of the wanted element
 * @param value - the new value to be set
 */
void swigCArraySet(double*, int index, double value) {
    a[index] = value;
}
%}

%rename(delete_array) free(void*);

// these functions are to be used for python structures
%pythoncode %{
def swigPyListToCArray(pyList):
    '''
    converts python list to C-like array
    @param pyList - python list
    @return - C array
    '''
    cArray = swigNewCArray( len(pyList) )
    for i in xrange( len(pyList) ):
        swigCArraySet(cArray, i, pyList[i])
    return cArray

def swigCArrayToPyList(cArray, arraySize):
    '''
    converts C-like array to python list
    @param cArray - C array
    @param arraySize - size of the C array
    @return - python list
    '''
    pyList = [1] * arraySize
    for i in xrange(arraySize):
        pyList[i] = swigCArrayGet(cArray, i)
    return pyList
%}
