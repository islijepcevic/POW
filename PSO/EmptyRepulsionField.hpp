/*
 * EmptyRepulsionField.hpp
 *
 * a class that is used for repulsion field when no repulsion is to be used
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __EMPTY_REPULSION_FIELD__
#define __EMPTY_REPULSION_FIELD__

#include "RepulsionField.hpp"

#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

namespace PSO {

/**
 * EmptyRepulsionField does not provide any repulsion field. It is used when
 * the user doesn't want repulsion field
 */
class EmptyRepulsionField : public RepulsionField {
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

    EmptyRepulsionField();

    virtual ~EmptyRepulsionField();

    // Override
    virtual void addRepeller(const std::vector<double>& position);

    // Override
    virtual void apply(Particle& particle, const PsoSpace& space) const ;
};

} // namespace PSO

BOOST_CLASS_EXPORT_KEY(PSO::EmptyRepulsionField);

#endif // __EMPTY_REPULSION_FIELD__
