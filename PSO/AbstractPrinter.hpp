/*
 * AbstractPrinter.hpp
 *
 * abstraction of printer class that acts as a observer to the PSO and prints
 * data to log
 *
 * printing will be done only from the master process, and only that instance of
 * PSO class will have references to printers
 *
 * PSO class might have references to more than one printer, because various
 * printers can be used for different prints. e.g. some might print data to
 * console, and others might write data to log
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __ABSTRACT_PRINTER__
#define __ABSTRACT_PRINTER__

#include "PSOForward.hpp"

namespace PSO {

class AbstractPrinter {
public:

    /*
     * constructor
     */
    AbstractPrinter() {
    }

    /*
     * destructor
     */
    virtual ~AbstractPrinter() {
    }

    /*
     * method to be called upon the beginning of new PSO algorithm repetition
     * @param pso - pushed instance of PSO class from which data will be taken
     */
    virtual void printRepetitionStart(const PSO& pso) const = 0;

    /*
     * method to be called upon the beginning of new iteration in PSO algorithm
     * @param pso - pushed instance of PSO class from which data will be taken
     */
    virtual void printIterationStart(const PSO& pso) const = 0;

    /*
     * method to be called after the end of an iteration in PSO algorithm
     * @param pso - pushed instance of PSO class from which data will be taken
     */
    virtual void printIterationEnd(const PSO& pso) const = 0;


    // here, add methods for all different kinds and places to print data
};

} // namespace PSO

#endif // __ABSTRACT_PRINTER__
