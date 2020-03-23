#ifndef ESPRESSO_PARTICLE_INDEX_HPP
#define ESPRESSO_PARTICLE_INDEX_HPP

#include "ParticleList.hpp"

#include <vector>

/**
 * @brief Find local particles by id.
 *
 * If a particles is present on this mpi rank, either
 * as a local particles or as a ghost, a pointer to it
 * is returned, otherwise null.
 *
 * @param id of the particle to look up.
 *
 * @return Pointer to particle or nullptr.
 **/
inline Particle *get_local_particle_data(int id) {
  extern std::vector<Particle *> local_particles;

  if (id >= local_particles.size())
    return nullptr;

  return local_particles[id];
}

/**
 * @brief Update local particle index.
 *
 * Update the entry for a particle in the local particle
 * index.
 *
 * @param id of the particle to up-date.
 * @param p Pointer to the particle.
 **/
inline void set_local_particle_data(int id, Particle *p) {
  extern std::vector<Particle *> local_particles;

  if (id >= local_particles.size())
    local_particles.resize(id + 1);

  local_particles[id] = p;
}

/**
 * @brief Get the maximal particle ever seen on this node.
 *
 * This returns the highest particle id ever encountered on
 * this node, or -1 if there are no particles on this node.
 */
inline int get_local_max_seen_particle() {
  extern std::vector<Particle *> local_particles;

  auto it = std::find_if(local_particles.rbegin(), local_particles.rend(),
                         [](const Particle *p) { return p != nullptr; });

  return (it != local_particles.rend()) ? (*it)->identity() : -1;
}

/** Update the entries in \ref local_particles for all particles in the list pl.
 *  @param pl the list to put in.
 */
void update_local_particles(const ParticleList *pl);

/** Append a particle at the end of a particle list.
 *  Reallocate particles if necessary!
 *  This procedure cares for \ref local_particles.
 *  \param plist List to append the particle to.
 *  \param part  Particle to append.
 *  \return Pointer to new location of the particle.
 */
Particle *append_indexed_particle(ParticleList *plist, Particle &&part);

#endif // ESPRESSO_PARTICLE_INDEX_HPP
