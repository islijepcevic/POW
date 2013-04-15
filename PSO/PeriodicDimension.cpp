#include "PeriodicDimension.hpp"

PeriodicDimension::PeriodicDimension(const double _lower,
                                    const double _higher) :
    Dimension(_lower, _higher) {

}

PeriodicDimension::~PeriodicDimension() {
}

std::pair<double, double> checkBoundaries(double position,
                                            double velocity) const {

    // TODO
}
