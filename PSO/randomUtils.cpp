#include "randomUtils.hpp"

#include <cstdlib>
#include <ctime>

double randDouble(double lo, double hi) {

    double number = (double)rand() / RAND_MAX;
    return lo + number * (hi - lo);
}

void initRandomSeed() {
    srand(time(NULL));
}
