#pragma once

#include "cinder/gl/gl.h"
#include "core/particle.h"
#include "core/container.h"
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
  ParticleManager();

  //ParticleManager(vector<Particle> particles);

  ParticleManager(size_t height, size_t length);

  //Functions
  vector<Particle> Update();
  /**
   * Checks for all particle-particle collisions and updates their velocities accordingly.
   * @return
   */
  vector<Particle> CheckParticleCollisions();
  vector<Particle> CheckBarrierCollisions();
  vector<Particle> AddParticle(const Particle& particle);

  //Getters-Setters
  vector<Particle> GetParticles();
  size_t GetNumberOfParticles();
  size_t GetHeight() const;
  size_t GetLength() const;

 private:
  vector<Particle> particles_;
  size_t number_of_particles_;
  size_t height_;
  size_t length_;
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
