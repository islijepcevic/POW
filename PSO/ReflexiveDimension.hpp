/*
 * ReflexiveDimension.hpp
 *
 * Subclass of Dimension with reflexive boundary condition
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __REFLEXIVE_DIMENSION__
#define __REFLEXIVE_DIMENSION__

#include <utility>
#include <stdexcept>
//#include <boost/mpi/packed_iarchive.hpp>
//#include <boost/mpi/packed_oarchive.hpp>
//#include <boost/serialization/serialization.hpp>
//#include <boost/serialization/base_object.hpp>

#include "Dimension.hpp"

namespace PSO {

class ReflexiveDimension : public Dimension {
private:
    
//    // BOOST SERIALIZATION
//    friend class boost::serialization::access;
//
//    /*
//     * method that for serializing and deserializing objects of this class
//     * @param ar - archive stream
//     * @param version - don't know, not used
//     */
//    template<class Archive>
//    void serialize(Archive& ar, const unsigned int version) {
//        ar.template register_type<Dimension>();
//        // serialize base class information
//        //ar & boost::serialization::base_object<Dimension>(*this);
//        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Dimension);
//    }

public:

    /*
     * constructor
     */
    ReflexiveDimension(const double _lower, const double _higher);

    /*
     * destructor
     */
    virtual ~ReflexiveDimension();

    // Override
    virtual std::pair<double, double>
        checkBoundaries(double position, double velocity) const;

    // Override
    virtual double calculateShortestDistance(double pos1, double pos2) const;
};

//BOOST_CLASS_EXPORT(ReflexiveDimension);

} // namespace PSO

#endif // __REFLEXIVE_DIMENSION__
