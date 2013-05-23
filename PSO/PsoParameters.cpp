/*
 * PsoParameters.cpp
 *
 * class for c++ code, similar to Parser in python code
 * serves as collection of parameters
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "PsoParameters.hpp"

namespace PSO {

PsoParameters::PsoParameters() {
}

PsoParameters::~PsoParameters() {
}

int PsoParameters::getIntParam(const std::string& key) const {
    return parametersInt.at(key);
}

void PsoParameters::setIntParam(const std::string& key, const int value) {
    parametersInt.insert( std::pair<std::string, int>(key, value) );
}

double PsoParameters::getDoubleParam(const std::string& key) const {
    return parametersDouble.at(key);
}

void PsoParameters::setDoubleParam(const std::string& key,
                                    const double value) {
    parametersDouble.insert( std::pair<std::string, double>(key, value) );
}

std::string PsoParameters::getStringParam(const std::string& key) const {
    return parametersString.at(key);
}

void PsoParameters::setStringParam(const std::string& key,
                                    const std::string& value) {
    parametersString.insert( std::pair<std::string, std::string>(key, value) );
}

const std::vector<int>& PsoParameters::getIntArrayParam(
                                        const std::string& key) const {
    return parametersArrayInt.at(key);
}

void PsoParameters::setIntArrayParam(const std::string& key,
                                    const std::vector<int>& value) {
    parametersArrayInt.insert(
        std::pair<std::string, std::vector<int> >(key, value)
    );
}

const std::vector<double>& PsoParameters::getDoubleArrayParam(
                                            const std::string& key) const {
    return parametersArrayDouble.at(key);
}

void PsoParameters::setDoubleArrayParam(const std::string& key,
                                        const std::vector<double>& value) {

    parametersArrayDouble.insert(
        std::pair<std::string, std::vector<double> >(key, value)
    );
}

const std::vector<std::string>& PsoParameters::getStringArrayParam(
                                            const std::string& key) const {

    return parametersArrayString.at(key);
}

void PsoParameters::setStringArrayParam(const std::string& key,
                        const std::vector<std::string>& value) {

    parametersArrayString.insert(
        std::pair<std::string, std::vector<std::string> >(key, value)
    );
}

} // namespace PSO
