#include "randomUtils.hpp"

#include <cstdlib>

double randDouble(double lo, double hi) {

    double number = (double)rand() / RAND_MAX;
    return lo + number * (hi - lo);
}
