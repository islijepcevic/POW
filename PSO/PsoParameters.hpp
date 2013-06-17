/**
 * PsoParameters.hpp
 *
 * class for c++ code, similar to Parser in python code
 * serves as collection of parameters
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __PSO_PARAMETERS__
#define __PSO_PARAMETERS__

#include <map>
#include <vector>
#include <string>

namespace PSO {

class PsoParameters {
private:
    // rely on existing exceptions if maps dereferenced wrongly
    std::map<std::string, int> parametersInt;
    std::map<std::string, double> parametersDouble;
    std::map<std::string, std::string> parametersString;
    std::map<std::string, std::vector<int> > parametersArrayInt;
    std::map<std::string, std::vector<double> > parametersArrayDouble;
    std::map<std::string, std::vector<std::string> > parametersArrayString;

public: // this should be protected
    
    /**
     * setter for int parameter
     */
    void setIntParam(const std::string& key, const int value);

     /**
     * setter for double parameter
     */
    void setDoubleParam(const std::string& key, const double value);
     
    /**
     * setter for string parameter
     */
    void setStringParam(const std::string& key, const std::string& value);

     /**
     * setter for int array parameter
     */
    void setIntArrayParam(const std::string& key,
                        const std::vector<int>& value);
     
    /**
     * setter for double array parameter
     */
    void setDoubleArrayParam(const std::string& key,
                            const std::vector<double>& value);

    /**
     * setter for string array parameter
     */
    void setStringArrayParam(const std::string& key,
                            const std::vector<std::string>& value);

// this is really public now

    /**
     * constructor
     */
    PsoParameters();

    /**
     * copy constructor
     */
    PsoParameters(const PsoParameters& _params);

    /**
     * destructor
     */
    virtual ~PsoParameters();

    /**
     * getter for int parameter
     */
    int getIntParam(const std::string& key) const;

    /**
     * getter for double parameter
     */
    double getDoubleParam(const std::string& key) const;

    /**
     * getter for string parameter
     */
    std::string getStringParam(const std::string& key) const;

    /**
     * getter for int array parameter
     */
    const std::vector<int>& getIntArrayParam(const std::string& key) const;
    
    /**
     * getter for double array parameter
     */
    const std::vector<double>& getDoubleArrayParam(const std::string& key) const;

    /**
     * getter for string array parameter
     */
    const std::vector<std::string>& getStringArrayParam(const std::string& key) const;

};

} // namespace PSO

#endif // __PSO_PARAMETERS__
