/*
 * BaseParameters.hpp
 *
 * Basic class providing parameters
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __BASE_PARAMETERS__
#define __BASE_PARAMETERS__

#include <map>
#include <vector>
#include <string>

namespace PSO {

class BaseParameters {
private:
    // rely on existing exceptions if maps dereferenced wrongly
    std::map<std::string, int> parametersInt;
    std::map<std::string, double> parametersDouble;
    std::map<std::string, std::string> parametersString;
    std::map<std::string, std::vector<int> > parametersArrayInt;
    std::map<std::string, std::vector<double> > parametersArrayDouble;
    std::map<std::string, std::vector<std::string> > parametersArrayString;

public: // this should be protected
    
    /*
     * setter for int parameter
     */
    void _setIntParam(const std::string& key, const int value);

     /*
     * setter for double parameter
     */
    void _setDoubleParam(const std::string& key, const double value);
     
    /*
     * setter for string parameter
     */
    void _setStringParam(const std::string& key, const std::string value);

     /*
     * setter for int array parameter
     */
    void _setIntArrayParam(const std::string& key,
                        const std::vector<int>& value);
     
    /*
     * setter for double array parameter
     */
    void _setDoubleArrayParam(const std::string& key,
                            const std::vector<double>& value);

    /*
     * setter for string array parameter
     */
    void _setStringArrayParam(const std::string& key,
                            const std::vector<std::string>& value);

// this is really public now

    /*
     * constructor
     */
    BaseParameters();

    /*
     * destructor
     */
    virtual ~BaseParameters();

    /*
     * getter for int parameter
     */
    int getIntParam(const std::string& key) const;

    /*
     * getter for double parameter
     */
    double getDoubleParam(const std::string& key) const;

    /*
     * getter for string parameter
     */
    std::string getStringParam(const std::string& key) const;

    /*
     * getter for int array parameter
     */
    const std::vector<int>& getIntArrayParam(const std::string& key) const;
    
    /*
     * getter for double array parameter
     */
    const std::vector<double>& getDoubleArrayParam(const std::string& key) const;

    /*
     * getter for string array parameter
     */
    const std::vector<std::string>& getStringArrayParam(const std::string& key) const;

};

} // namespace PSO

#endif // __BASE_PARAMETERS__
