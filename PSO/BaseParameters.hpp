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
    std::map<std::string, std::vector<int>& > parametersArrayInt;
    std::map<std::string, std::vector<double>& > parametersArrayDouble;
    std::map<std::string, std::vector<std::string>& > parametersArrayString;

protected:
    
    /*
     * setter for int parameter
     */
    void setIntParam(const std::string& key, const int value);

     /*
     * setter for double parameter
     */
    void setDoubleParam(const std::string& key, const double value);
     
    /*
     * setter for string parameter
     */
    void setStringParam(const std::string& key, const std::string value);

     /*
     * setter for int array parameter
     */
    void setIntArrayParam(const std::string& key,
                        const std::vector<int>& value);
     
    /*
     * setter for double array parameter
     */
    void setDoubleArrayParam(const std::string& key,
                            const std::vector<double>& value);

    /*
     * setter for string array parameter
     */
    void setStringArrayParam(const std::string& key,
                            const std::vector<std::string>& value);

public:

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
    std::vector<int>& getIntArrayParam(const std::string& key) const;
    
    /*
     * getter for double array parameter
     */
    std::vector<double>& getDoubleArrayParam(const std::string& key) const;

    /*
     * getter for string array parameter
     */
    std::vector<std::string>& getStringArrayParam(const std::string& key) const;

};

} // namespace PSO

#endif // __BASE_PARAMETERS__
