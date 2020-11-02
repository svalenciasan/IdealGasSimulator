#include "core/particle_manager.h"
#include "core/particle.h"

using idealgas::particle::Particle;
using glm::distance;
using glm::dot;
using glm::length;

namespace idealgas {

namespace particlemanager {
/**
* Constructors
*/
ParticleManager::ParticleManager() {

}

ParticleManager::ParticleManager(vector<Particle> particles) {
  particles_ = particles;
}

/**
* Functions
*/
vector<Particle> ParticleManager::Update() {
  //Updates the velocity of all particles
  CheckParticleCollisions();
  for(Particle particle : particles_) {
    particle.Update();
  }
  return particles_;
}

/**
* Getters-Setters
*/
vector<Particle> ParticleManager::GetParticles() {
  return particles_;
}
size_t ParticleManager::GetNumberOfParticles() {
  return number_of_particles_;
}

/**
* Private
*/
vector<Particle> ParticleManager::CheckParticleCollisions() {
  for (Particle particle : particles_) {
    for (Particle second_particle : particles_) {
      long particle_radius = particle.GetRadius();
      vec2 particle_position = particle.GetPosition();
      vec2 particle_velocity = particle.GetVelocity();

      long second_particle_radius = second_particle.GetRadius();
      vec2 second_particle_position = second_particle.GetPosition();
      vec2 second_particle_velocity = second_particle.GetVelocity();

      vec2 velocity_difference = particle_velocity - second_particle_velocity;
      vec2 position_difference = particle_position - second_particle_position;

      bool colliding = dot(velocity_difference, position_difference) < 0;
      //If the particles are touching
      if (distance(particle_position, second_particle_position) < particle_radius + second_particle_radius && colliding) {
        vec2 new_velocity = CalculateParticleCollisionVelocity(particle, second_particle);
        particle.SetVelocity(new_velocity);
      }
    }
  }
  return particles_;
}

vec2 ParticleManager::CalculateParticleCollisionVelocity(const Particle& particle, const Particle& second_particle) const{
  vec2 particle_position = particle.GetPosition();
  vec2 particle_velocity = particle.GetVelocity();

  vec2 second_particle_position = second_particle.GetPosition();
  vec2 second_particle_velocity = second_particle.GetVelocity();

  vec2 velocity_difference = particle_velocity - second_particle_velocity;
  vec2 position_difference = particle_position - second_particle_position;

  vec2 new_velocity = particle_velocity
                      - (dot(velocity_difference, position_difference)
                         / pow(length(particle_position - second_particle_position), 2))
                        * (particle_position - second_particle_position);
  return new_velocity;
}

}//namespace particlemanager

}//namespace idealgas
