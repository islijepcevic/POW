/*
 * PeriodicDimension.hpp
 *
 * Subclass of Dimension with periodic boundary condition
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __PERIODIC_DIMENSION__
#define __PERIODIC_DIMENSION__

#include <utility>
#include <stdexcept>
//#include <boost/mpi/packed_iarchive.hpp>
//#include <boost/mpi/packed_oarchive.hpp>
//#include <boost/serialization/serialization.hpp>
//#include <boost/serialization/export.hpp>
//#include <boost/serialization/base_object.hpp>

#include "Dimension.hpp"

namespace PSO {

class PeriodicDimension : public Dimension {
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
    PeriodicDimension(const double _lower, const double _higher);

    /*
     * destructor
     */
    virtual ~PeriodicDimension();

    // Override
    virtual std::pair<double, double>
        checkBoundaries(double position, double velocity) const;

    // Override
    virtual double calculateShortestDistance(double pos1, double pos2) const;
};


} // namespace PSO
//BOOST_CLASS_EXPORT(PSO::PeriodicDimension)

#endif // __PERIODIC_DIMENSION__
