#ifndef MPM_HDF5_H_
#define MPM_HDF5_H_

// HDF5
#include "hdf5.h"
#include "hdf5_hl.h"

namespace mpm {

// Define a struct of particle
typedef struct HDF5Particle {
  // Index
  mpm::Index id;
  // Mass
  double mass;
  // Coordinates
  double coord_x, coord_y, coord_z;
  // Velocity
  double velocity_x, velocity_y, velocity_z;
  // Stresses
  double stress_xx, stress_yy, stress_zz;
  double tau_xy, tau_yz, tau_xz;
  // Strains
  double strain_xx, strain_yy, strain_zz;
  double gamma_xy, gamma_yz, gamma_xz;
  // Status
  bool status;
} HDF5Particle;

}  // namespace mpm

#endif  // MPM_HDF5_H_
