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
  ParticleManager();

  ParticleManager(vector<Particle> particles);

  //Functions
  vector<Particle> Update();

  //Getters-Setters
  vector<Particle> GetParticles();

  size_t GetNumberOfParticles();
 private:
  vector<Particle> particles_;
  size_t number_of_particles_;
  //Helper functions
  vector<Particle> CheckParticleCollisions();
  vec2 CalculateParticleCollisionVelocity(const Particle& particle, const Particle& second_particle) const;
  };

}//namespace particlemanager

}//namespace ideal_gas
