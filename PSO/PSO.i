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
#include "PSOForward.hpp"
#include "SwarmForward.hpp"
#include "PsoSpaceForward.hpp"
#include "Dimension.hpp"
#include "PeriodicDimension.hpp"
#include "ReflexiveDimension.hpp"
#include "constants.hpp"
#include "randomUtils.hpp"
#include "Particle.hpp"
#include "AbstractFitnessProxy.hpp"
#include "PsoSpace.hpp"
#include "PsoParameters.hpp"
#include "AbstractPrinter.hpp"
#include "SpaceFactory.hpp"
#include "Swarm.hpp"
#include "PSO.hpp"
#include "Neighbourhood.hpp"
#include "IndexedNeighbourhood.hpp"
#include "GeographicNeighbourhood.hpp"
#include "NeighbourhoodFactory.hpp"
#include <vector>
#include <string>
#include <mpi.h>
#include <boost/mpi.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
%}


// DIRECTORS - they enable inheritance and polymorphism from c++ to python
%feature("director") AbstractFitnessProxy;
%feature("director") AbstractPrinter;

// INCLUSION OF ALL THE FILES/CLASESS IMPLEMENTED IN C++

// this one also needs to be here so that std::vector can be mapped to python
%include <std_vector.i>
%include <std_string.i>

// this needs to be included in order to map python''s MPI.comm into c/c++
// MPI_comm
%include mpi4py/mpi4py.i
%mpi4py_typemap(Comm, MPI_Comm);

// this is instead of rewriting all the code here
// this will be accessible in python code
%include "PsoSpaceForward.hpp"      
%include "SwarmForward.hpp"
%include "Particle.hpp"             // needs PsoSpaceForward
%include "Dimension.hpp"            
%include "PsoSpace.hpp"             // needs Dimension and Particle
%include "PsoParameters.hpp"
%include "AbstractFitnessProxy.hpp"
%include "Swarm.hpp"                // needs Particle and PsoSpace
%include "PSOForward.hpp"
%include "AbstractPrinter.hpp"      // needs PSOForward
%include "Neighbourhood.hpp"        // needs Swarmforward and Particle
%include "PSO.hpp"                  // needs a lot of them
%include "SpaceFactory.hpp"         // needs PsoSpace and Dimension

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
void swigCArraySet(double* a, int index, double value) {
    a[index] = value;
}

/*
 * creates and returns a new c++ string of length n and filled with characters
 * 'a'
 * @param n - length of new string
 * @return - the string
 */
std::string swigNewCppString(unsigned int n) {
    std::string s;
    s.reserve(n);
    return s;
}

/*
 * creates a new c++ vector of arbitrary type
 * @return - an empty vector
 */
template<class T>
std::vector<T> swigNewCppVector() {
    std::vector<T> vec;
    return vec;
}

%}

%rename(delete_array) free(void*);

// instantiate the function swigNewCppVector()
%template(swigNewIntVector) swigNewCppVector<int>;
%template(swigNewDblVector) swigNewCppVector<double>;
%template(swigNewStrVector) swigNewCppVector<std::string>;

// instantiate the vector class; if this is not done, the memory leak appears
// because this SWIG file only sees the declaration of vector<T>. This is not a
// "complete" class and it does not have a callable destructor, so it is needed
// to instantiate the templated type to have the definition of the "complete"
// type
%template(vecint) std::vector<int>;
%template(vecdbl) std::vector<double>;
%template(vecstr) std::vector<std::string>;
%template(vecdim) std::vector<PSO::Dimension*>;
%template(vecpart) std::vector<PSO::Particle>;
%template(vecprint) std::vector<PSO::AbstractPrinter*>;

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


def swigPyToCppString(pyStr):
    '''
    converts python string into the c++ string
    @param pyStr - python string
    @param - c++ string
    '''
    #return pyStr
    cppStr = swigNewCppString(len(pyStr))
    for i in xrange(len(pyStr)):
        #cppStr[i] = pyStr[i]
        cppStr.push_back(pyStr[i])
    return cppStr

def swigPyListToCppVector(pyList, vartype):
    '''
    this method converts python list to c++ vector
    it is used to put data from python list into the c++ class
    @param pyList - python list
    @param vartype - type of the data in pyList;
            supported types: int, float, str
    @return - c++ vector with same data
    '''

    vector = None

    if vartype == 'array int':
        vector = swigNewIntVector()
    elif vartype == 'array float':
        vector = swigNewDblVector()
    elif vartype == 'array str':
        vector = swigNewStrVector()
    else:
        raise ValueError("wrong vartype supported to swigPyListToCppVector")

    vector.reserve( len(pyList) )

    for elem in pyList:
        vector.push_back(elem)

    return vector

def swigCppVectorToPyList(vector):
    '''
    this method converts c++ vector to python list
    '''
    pyList = [1] * vector.size()
    for i in xrange(vector.size()):
        pyList[i] = vector[i]
    return pyList
    


class VectorAdaptor(list):
    '''
    this class is adaptor that inherits from python list, and has an adaptee
    c++ std::vector

    it is used in python where the c++ vector is in the background
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

// this beautiful part of code makes it possible that when Python function is
// called from c++, and python error is thrown, the correct error/exception is
// shown together with the traceback
// If this is not here, then all I get is Swig::DirectorMethodException (which
// is wrong)
%feature("director:except") {
    if( $error != NULL ) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch( &ptype, &pvalue, &ptraceback );
        PyErr_Restore( ptype, pvalue, ptraceback );
        PyErr_Print();
        Py_Exit(1);
    }
}
