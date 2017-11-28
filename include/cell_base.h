#ifndef MPM_CELL_BASE_H_
#define MPM_CELL_BASE_H_

#include <array>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "Eigen/Dense"

#include "handler.h"
#include "node_base.h"
#include "shapefn.h"

namespace mpm {

// Global index type for the cell
using Index = unsigned long long;

// CellBase class
//! \brief Base class that stores the information about cells
//! \details CellBase class: id_ and coordinates.
//! \tparam Tdim Dimension
template <unsigned Tdim>
class CellBase {
 public:
  //! Define a vector of size dimension
  using VectorDim = Eigen::Matrix<double, Tdim, 1>;

  // Constructor with id and coordinates
  CellBase(Index id, unsigned nnodes);

  // Constructor with id, coordinates and shapefn
  CellBase(Index id, unsigned nnodes,
           const std::shared_ptr<ShapeFn<Tdim>>& shapefnptr);

  //! Destructor
  virtual ~CellBase(){};

  //! Delete copy constructor
  CellBase(const CellBase<Tdim>&) = delete;

  //! Delete assignement operator
  CellBase& operator=(const CellBase<Tdim>&) = delete;

  //! Return id of the cell
  Index id() const { return id_; }

  //! Number of nodes
  unsigned nnodes() const { return nodes_.size(); }

  //! Assign shape function
  bool shapefn(const std::shared_ptr<ShapeFn<Tdim>>& shapefnptr);

  //! Number of shape functions
  unsigned nfunctions() const { return this->shapefn_->nfunctions(); };

  //! Add node to cell
  bool add_node(unsigned local_id, const std::shared_ptr<NodeBase<Tdim>>& node);

  //! Add neighbouring cell
  bool add_neighbour(unsigned id,
                     const std::shared_ptr<CellBase<Tdim>>& neighbour);

  //! Number of neighbours
  unsigned nneighbours() const { return neighbour_cells_.size(); }

 private:
  //! cell id
  Index id_{std::numeric_limits<Index>::max()};

  //! Number of nodes
  unsigned nnodes_{0};

  //! Container of node pointers (local id, node pointer)
  Handler<NodeBase<Tdim>> nodes_;

  //! Container of cell neighbours
  Handler<CellBase<Tdim>> neighbour_cells_;

  //! Shape function
  std::shared_ptr<ShapeFn<Tdim>> shapefn_;
};  // CellBase class
}  // mpm namespace

#include "cell_base.tcc"

#endif  // MPM_CELL_BASE_H_