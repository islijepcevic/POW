/*
 * randomUtils.hpp
 *
 * this file contains functions that provide random numbers
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */

/*
 * this function generates the random number in the given bounds
 * function expects that srand has already been called
 * @param lo - lower bound
 * @param hi - higher bound
 * @return - a random double
 */
double randDouble(double lo, double hi);
