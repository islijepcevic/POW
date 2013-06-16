/*
 * PotentialRepulsionField.hpp
 *
 * a class that is used for repulsion field with simple potential repulsion
 * factor
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __POTENTIAL_REPULSION_FIELD__
#define __POTENTIAL_REPULSION_FIELD__

#include "RepulsionField.hpp"

#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

namespace PSO {

/**
 * PotentialRepulsionField does not provide any repulsion field. It is used when
 * the user doesn't want repulsion field
 */
class PotentialRepulsionField : public RepulsionField {
private:

    // boost serialization
    friend class boost::serialization::access;

    /**
     * method that for serializing and deserializing objects of this class
     * @param ar - archive stream
     * @param version - don't know, not used
     */
    template<class archive>
    void serialize(archive &ar, const unsigned int version) {
        //ar.template register_type<Dimension>();
        ar & boost::serialization::base_object<RepulsionField>(*this);
    }

public:

    PotentialRepulsionField();

    PotentialRepulsionField(double _repulsionFactor);

    virtual ~PotentialRepulsionField();

    // Override
    virtual void addRepeller(const std::vector<double>& position);

    // Override
    virtual void apply(Particle& particle, const PsoSpace& space) const;
};

} // namespace PSO

BOOST_CLASS_EXPORT_KEY(PSO::PotentialRepulsionField);

#endif // __POTENTIAL_REPULSION_FIELD__
