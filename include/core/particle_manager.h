#pragma once

#include "cinder/gl/gl.h"
#include "core/particle.h"
#include <vector>

using std::string;
using std::vector;
using glm::vec2;
using idealgas::particle::Particle;

namespace idealgas {

namespace particlemanager {

class ParticleManager {
 public:
  //Constructor
  ParticleManager() = default;
  ParticleManager(vec2 top_left_corner, vec2 bottom_right_corner);

  //Functions
  vector<Particle> Update();
  /**
   * Checks for all particle-particle collisions and updates their velocities accordingly.
   * @return
   */
  vector<Particle> CheckParticleCollisions();
  vector<Particle> CheckBarrierCollisions();
  vector<Particle> AddParticle(const Particle& particle);
  vector<Particle> ClearParticles();
  //Getters-Setters
  vector<Particle> GetParticles() const;
  size_t GetNumberOfParticles() const;

 private:
  vector<Particle> particles_;
  size_t number_of_particles_ = 0;
  vec2 top_left_corner_;
  vec2 bottom_right_corner_;
  //Helper functions
  /**
   * Calculates the resulting velocity of a collision between 2 particles.
   * @param particle
   * @param second_particle
   * @return
   */
  vec2 CalculateParticleCollision(const Particle& particle, const Particle& second_particle) const;
  vec2 CalculateBarrierCollision(const Particle& particle) const;
  };

}//namespace particlemanager

}//namespace ideal_gas
