/*
 * BaseParameters.cpp
 *
 * Basic class providing parameters
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#include "BaseParameters.hpp"

namespace PSO {

BaseParameters::BaseParameters() {
}

BaseParameters::~BaseParameters() {
}

int BaseParameters::getIntParam(const std::string& key) const {
    return parametersInt.at(key);
}

void BaseParameters::setIntParam(const std::string& key, const int value) {
    parametersInt.insert( std::pair<std::string, int>(key, value) );
}

double BaseParameters::getDoubleParam(const std::string& key) const {
    return parametersDouble.at(key);
}

void BaseParameters::setDoubleParam(const std::string& key,
                                    const double value) {
    parametersDouble.insert( std::pair<std::string, double>(key, value) );
}

std::string BaseParameters::getStringParam(const std::string& key) const {
    return parametersString.at(key);
}

void BaseParameters::setStringParam(const std::string& key,
                                    const std::string value) {
    parametersString.insert( std::pair<std::string, std::string>(key, value) );
}

std::vector<int>& BaseParameters::getIntArrayParam(
                                        const std::string& key) const {
    return parametersArrayInt.at(key);
}

void BaseParameters::setIntArrayParam(const std::string& key,
                                    const std::vector<int>& value) {
    parametersArrayInt.insert(
        std::pair<std::string, std::vector<int>& >(key, value)
    );
}

std::vector<double>& BaseParameters::getDoubleArrayParam(
                                            const std::string& key) const {
    return parametersArrayDouble.at(key);
}

void BaseParameters::setDoubleArrayParam(const std::string& key,
                                        const std::vector<double>& value) {

    parametersArrayDouble.insert(
        std::pair<std::string, std::vector<double>& >(key, value)
    );
}

std::vector<std::string>& BaseParameters::getStringArrayParam(
                                            const std::string& key) const {

    return parametersArrayString.at(key);
}

void BaseParameters::setStringArrayParam(const std::string& key,
                        const std::vector<std::string>& value) {

    parametersArrayString.insert(
        std::pair<std::string, std::vector<std::string>& >(key, value)
    );
}

} // namespace PSO
