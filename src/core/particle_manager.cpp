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
ParticleManager::ParticleManager() = default;

ParticleManager::ParticleManager(size_t height, size_t length){
  height_ = height;
  length_ = length;
  number_of_particles_ = 0;
}

/**
* Public Functions
*/
vector<Particle> ParticleManager::Update() {
  //Updates all particle positions
  for(Particle& particle : particles_) {
    particle.Update();
  }
  return particles_;
}

vector<Particle> ParticleManager::CheckParticleCollisions() {
  for (size_t currentIndex = 0; currentIndex < particles_.size(); currentIndex++) {
    Particle currParticle = particles_.at(currentIndex);

    for (size_t compareIndex = currentIndex + 1; compareIndex < particles_.size(); compareIndex++) {
      Particle compareParticle = particles_.at(compareIndex);

      float particle_radius = currParticle.GetRadius();
      vec2 particle_position = currParticle.GetPosition();
      vec2 particle_velocity = currParticle.GetVelocity();

      float second_particle_radius = compareParticle.GetRadius();
      vec2 second_particle_position = compareParticle.GetPosition();
      vec2 second_particle_velocity = compareParticle.GetVelocity();

      vec2 velocity_difference = particle_velocity - second_particle_velocity;
      vec2 position_difference = particle_position - second_particle_position;

      bool colliding = dot(velocity_difference, position_difference) < 0;
      //If the particles are touching
      if (distance(particle_position, second_particle_position) < particle_radius + second_particle_radius && colliding) {
        vec2 new_curr_velocity = CalculateParticleCollision(currParticle, compareParticle);
        vec2 new_compare_velocity = CalculateParticleCollision(compareParticle, currParticle);

        currParticle.SetVelocity(new_curr_velocity);
        compareParticle.SetVelocity(new_compare_velocity);
      }
    }

  }
  return particles_;
}

vector<Particle> ParticleManager::CheckBarrierCollisions() {
  for (Particle& particle : particles_) {
    particle.SetVelocity(CalculateBarrierCollision(particle));
  }
  return particles_;
}

vector<Particle> ParticleManager::AddParticle(const Particle& particle) {
  particles_.push_back(particle);
  number_of_particles_++;
  return particles_;
}
/**
* Getters-Setters
*/
vector<Particle> ParticleManager::GetParticles() const{
  return particles_;
}
size_t ParticleManager::GetNumberOfParticles() const{
  return number_of_particles_;
}

/**
* Private
*/
vec2 ParticleManager::CalculateParticleCollision(const Particle& particle, const Particle& second_particle) const{
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
//TODO fix the barriers
vec2 ParticleManager::CalculateBarrierCollision(const Particle& particle) const {
  vec2 position = particle.GetPosition();
  vec2 velocity = particle.GetVelocity();
  float radius = particle.GetRadius();

  vec2 new_velocity = velocity;
  if (position.x <= 0 + radius && velocity.x < 0) {
    new_velocity = vec2(velocity.x * -1, velocity.y);
  }
  if (position.x >= length_ - radius && velocity.x > 0) {
    new_velocity = vec2(velocity.x * -1, velocity.y);
  }

  if (position.y <= 0 + radius && velocity.y < 0) {
    vec2 new_velocity(velocity.x, velocity.y * -1);
  }
  if (position.y >= height_ - radius && velocity.y > 0) {
    vec2 new_velocity(velocity.x, velocity.y * -1);
  }
  return new_velocity;
}

}//namespace particlemanager

}//namespace idealgas
