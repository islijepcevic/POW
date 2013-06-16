/**
 * RepulsionField.hpp
 *
 * an abstract class representing repulsion field
 *
 * author: Ivan Slijepcevic
 * e-mail: ivan.slijepcevic@epfl.ch
 */
#ifndef __REPULSION_FIELD__
#define __REPULSION_FIELD__

#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

#include "Particle.hpp"
#include "PsoSpace.hpp"

#include <vector>

namespace PSO {

class RepulsionField {
private:

    // BOOST SERIALIZATION
    friend class boost::serialization::access;

    /**
     * method that for serializing and deserializing objects of this class
     * @param ar - archive stream
     * @param version - don't know, not used
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & repellers;
    }

protected:

    /**
     * array of repellers, one entry is a vector of size = dimension
     */
    std::vector<std::vector<double> > repellers;

    /**
     * factor of repulsion field
     */
    double repulsionFactor;

public:

    /**
     * constructor
     */
    RepulsionField() {
    }

    RepulsionField(double _repulsionFactor) :
        repulsionFactor(_repulsionFactor) {
    }

    /**
     * destructor
     */
    virtual ~RepulsionField() {
    }

    /**
     * getter for number of repellers
     * @return number of repellers
     */
    virtual int getNoRepellers() const {
        return repellers.size();
    }

    /**
     * getter for a repeller
     * @param i - index of repeller
     * @return a repelling position
     */
    virtual std::vector<double> getRepeller(int i) const {
        return repellers[i];
    }
    
    /**
     * adds repeller to the field
     * @param position - position of new repeller
     */
    virtual void addRepeller(const std::vector<double>& position) = 0;

    /**
     * applies repulsion field to the particle
     * the repulsion field is applied after all the other updates in particle,
     * so it will affect both position and velocity
     * (if field affected before other updates, it would affect only on
     * velocity, which then affects position)
     * @param particle - particle that is affected by this repulsion field
     * @param space - space in which particle is moving
     */
    virtual void apply(Particle& particle, const PsoSpace& space) const = 0;
};

} // namespace PSO

BOOST_SERIALIZATION_ASSUME_ABSTRACT(PSO::RepulsionField);

#endif // __REPULSION_FIELD__
