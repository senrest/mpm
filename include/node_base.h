#ifndef MPM_NODE_BASE_H_
#define MPM_NODE_BASE_H_

#include <array>
#include <limits>
#include <map>
#include <vector>

#include <Eigen/Dense>

namespace mpm {

//! Global index type for the node_base
using Index = unsigned long long;

//! NodeBase base class for nodes
//! \brief Base class that stores the information about node_bases
//! \details NodeBase class: id_ and coordinates.
//! \tparam Tdim Dimension
template <unsigned Tdim>
class NodeBase {
 public:
  //! Define a vector of size dimension
  using VectorDim = Eigen::Matrix<double, Tdim, 1>;

  // Constructor with id and coordinates
  //! \param[in] id assign as the id_ of the node
  //! \param[in] coords coordinates of the node
  NodeBase(mpm::Index id, const VectorDim& coords){};

  //! Destructor
  virtual ~NodeBase(){};

  //! Delete copy constructor
  NodeBase(const NodeBase<Tdim>&) = delete;

  //! Delete assignement operator
  NodeBase& operator=(const NodeBase<Tdim>&) = delete;

  //! Return id of the nodebase
  virtual Index id() const = 0;

  //! Assign coordinates
  virtual void assign_coordinates(const VectorDim& coord) = 0;

  //! Return coordinates
  //! \retval coordinates_ return coordinates of the nodebase
  virtual VectorDim coordinates() const = 0;

  //! Initialise properties
  virtual void initialise() = 0;

  //! Return degrees of freedom
  virtual unsigned dof() const = 0;

  //! Assign status
  virtual void assign_status(bool status) = 0;

  //! Return status
  virtual bool status() const = 0;

  //! Update mass at the nodes from particle
  //! \param[in] update A boolean to update (true) or assign (false)
  //! \param[in] phase Index corresponding to the phase
  //! \param[in] mass Mass from the particles in a cell
  virtual void update_mass(bool update, unsigned phase, double mass) = 0;

  //! Return mass at a given node for a given phase
  virtual double mass(unsigned phase) const = 0;

  //! Update volume at the nodes from particle
  //! \param[in] update A boolean to update (true) or assign (false)
  //! \param[in] phase Index corresponding to the phase
  //! \param[in] volume Volume from the particles in a cell
  virtual void update_volume(bool update, unsigned phase, double volume) = 0;

  //! Return volume at a given node for a given phase
  virtual double volume(unsigned phase) const = 0;

  //! Update external force (body force / traction force)
  //! \param[in] update A boolean to update (true) or assign (false)
  //! \param[in] phase Index corresponding to the phase
  //! \param[in] force External force from the particles in a cell
  //! \retval status Update status
  virtual bool update_external_force(bool update, unsigned phase,
                                     const VectorDim& force) = 0;

  //! Return external force
  //! \param[in] phase Index corresponding to the phase
  virtual VectorDim external_force(unsigned phase) const = 0;

  //! Update internal force (body force / traction force)
  //! \param[in] update A boolean to update (true) or assign (false)
  //! \param[in] phase Index corresponding to the phase
  //! \param[in] force Internal force from the particles in a cell
  //! \retval status Update status
  virtual bool update_internal_force(bool update, unsigned phase,
                                     const VectorDim& force) = 0;

  //! Return internal force
  //! \param[in] phase Index corresponding to the phase
  virtual VectorDim internal_force(unsigned phase) const = 0;

  //! Update nodal momentum
  //! \param[in] update A boolean to update (true) or assign (false)
  //! \param[in] phase Index corresponding to the phase
  //! \param[in] momentum Momentum from the particles in a cell
  //! \retval status Update status
  virtual bool update_momentum(bool update, unsigned phase,
                               const VectorDim& momentum) = 0;

  //! Return momentum
  //! \param[in] phase Index corresponding to the phase
  virtual VectorDim momentum(unsigned phase) const = 0;

  //! Compute velocity from the momentum
  virtual void compute_velocity() = 0;

  //! Return velocity
  //! \param[in] phase Index corresponding to the phase
  virtual VectorDim velocity(unsigned phase) const = 0;

  //! Update nodal acceleration
  //! \param[in] update A boolean to update (true) or assign (false)
  //! \param[in] phase Index corresponding to the phase
  //! \param[in] acceleration Acceleration from the particles in a cell
  //! \retval status Update status
  virtual bool update_acceleration(bool update, unsigned phase,
                                   const VectorDim& acceleration) = 0;

  //! Return acceleration
  //! \param[in] phase Index corresponding to the phase
  virtual VectorDim acceleration(unsigned phase) const = 0;

  //! Compute acceleration
  virtual bool compute_acceleration_velocity(unsigned phase, double dt) = 0;

  //! Assign velocity constraint
  //! Directions can take values between 0 and Dim * Nphases
  //! \param[in] dir Direction of velocity constraint
  //! \param[in] velocity Applied velocity constraint
  virtual bool assign_velocity_constraint(unsigned dir, double velocity) = 0;

  //! Apply velocity constraints
  virtual void apply_velocity_constraints() = 0;

};  // NodeBase class
}  // namespace mpm

#endif  // MPM_NODE_BASE_H_
