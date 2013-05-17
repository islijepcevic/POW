/*
 * PSO.i
 *
 * this is the SWIG module file which links c++ module to python
 *
 * Author: Ivan Slijepcevic, ivan.slijepcevic@epfl.ch
 */
%module(directors="1") PSO

%{
// this is like include in C/C++ code
// put here what you need to compile everything
// not everything from here will be accessible in python code
#define SWIG_FILE_WITH_INIT
#include "PSO.hpp"
#include "AbstractFitness.hpp"
#include "AbstractSpace.hpp"
#include "BaseParameters.hpp"
#include "Particle.hpp"
#include <vector>
#include <string>
%}


// DIRECTORS - they enable inheritance and polymorphism from c++ to python
%feature("director") AbstractFitness;
%feature("director") BaseParameters;


// INCLUSION OF ALL THE FILES/CLASESS IMPLEMENTED IN C++
// this is instead of rewriting all the code here
// this will be accessible in python code
%include "BaseParameters.hpp"
%include "AbstractSpace.hpp"
%include "AbstractFitness.hpp"
%include "PSO.hpp"

// #############################################################################

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

def swigCppVectorToPyList(cppVector)
    '''
    '''
    pyList = [1] * cppVector.size()
    for i in xrange(arraySize):
        pyList[i] = cppVector[i]
    return pyList

class ListAdaptorToCppVector(list):
    '''
    this class is adaptor that inherits from python list, and has an adaptee
    c++ std::vector
    '''

class AdaptorToVector(list):
    '''
    this class is adaptor that inherits from python list, and has an adaptee
    c++ std::vector
    '''
    def __init__(self, vector):
        '''
        initializes the adaptor to accept the adaptee - the c++ vector
        @param vector - c++ vector
        '''
        list.__init__(self)
        self.vector = vector

    def __getitem__(self, key):
        '''
        method that is called when getting items with [] operator in python
        @param key - the index
        @return - the value from the c++ vector on the index key
        '''
        return vector[key]

    def __setitem__(self, key, item):
        '''
        method that is called when setting items with [] operator in python
        @param key - the index
        @param item - the value
        '''
        vector[key] = item 
    
%}
