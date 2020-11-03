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

ParticleManager::ParticleManager(vec2 top_left_corner, vec2 bottom_right_corner) {
  top_left_corner_ = top_left_corner;
  bottom_right_corner_ = bottom_right_corner;
}

/**
* Public Functions
*/
vector<Particle> ParticleManager::Update() {
  //Updates all particle positions
  for(Particle& particle : particles_) {
    particle.Update();
//    CalculateBarrierCollision(particle);
//    particle.SetPosition(FixOvershoot(particle));
  }
  return particles_;
}

vector<Particle> ParticleManager::CheckParticleCollisions() {
  for (size_t currentIndex = 0; currentIndex < particles_.size(); currentIndex++) {
    Particle& currParticle = particles_.at(currentIndex);

    for (size_t compareIndex = currentIndex + 1; compareIndex < particles_.size(); compareIndex++) {
      Particle& compareParticle = particles_.at(compareIndex);

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

vector<Particle> ParticleManager::ClearParticles() {
  while (number_of_particles_ > 0){
    particles_.pop_back();
    number_of_particles_--;
  }
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
                         / pow(length(position_difference), 2)
                        * position_difference);
  return new_velocity;
}

vec2 ParticleManager::CalculateBarrierCollision(const Particle& particle) const {
  vec2 position = particle.GetPosition();
  vec2 velocity = particle.GetVelocity();
  float radius = particle.GetRadius();

  float left_bound = top_left_corner_.x;
  float right_bound = bottom_right_corner_.x;
  float upper_bound = top_left_corner_.y;
  float lower_bound = bottom_right_corner_.y;

  vec2 new_velocity = velocity;
  //X bounds
  if (position.x <= left_bound + radius && new_velocity.x < 0) {
    new_velocity = vec2(new_velocity.x * -1, new_velocity.y);
  }
  if (position.x >= right_bound - radius && new_velocity.x > 0) {
    new_velocity = vec2(new_velocity.x * -1, new_velocity.y);
  }
  //Y bounds
  if (position.y >= lower_bound - radius && new_velocity.y > 0) {
    new_velocity = vec2(new_velocity.x, new_velocity.y * -1);
  }
  if (position.y <= upper_bound + radius && new_velocity.y < 0) {
    new_velocity = vec2(new_velocity.x, new_velocity.y * -1);
  }

  return new_velocity;
}

vec2 ParticleManager::FixOvershoot(const Particle& particle) const {
  vec2 position = particle.GetPosition();
  float radius = particle.GetRadius();

  float left_bound = top_left_corner_.x;
  float right_bound = bottom_right_corner_.x;
  float upper_bound = top_left_corner_.y;
  float lower_bound = bottom_right_corner_.y;

  vec2 new_position = position;
  //X bounds
  if (position.x <= left_bound + radius) {
    new_position = vec2(left_bound + (left_bound - position.x) + radius, new_position.y);
  }
  if (position.x >= right_bound - radius) {
    new_position = vec2(right_bound - (position.x - right_bound) - radius, new_position.y);
  }
  //Y bounds
  if (position.y >= lower_bound - radius) {
    new_position = vec2(new_position.x, lower_bound - (new_position.y - lower_bound) - radius);
  }
  if (position.y <= upper_bound + radius) {
    new_position = vec2(new_position.x, upper_bound + (upper_bound - new_position.y) + radius);  }

  return new_position;
}
}//namespace particlemanager

}//namespace idealgas
