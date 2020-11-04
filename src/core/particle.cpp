#include "core/particle.h"

namespace idealgas {

namespace particle {
/**
 * Constructors
 */
Particle::Particle(float radius, vec2& position, vec2& velocity) : kRadius(radius) {
  position_ = position;
  velocity_ = velocity;
}

/**
 * Functions
 */
 void Particle::Update() {
   position_ += velocity_;
 }

 /**
 * Getters-Setters
 */
 vec2 Particle::GetPosition() const{
   return position_;
 }

vec2 Particle::GetVelocity() const{
  return velocity_;
}

float Particle::GetRadius() const{
  return kRadius;
}

vec2 Particle::SetPosition(const vec2& position) {
 position_ = position;
 return position_;
}

vec2 Particle::SetVelocity(const vec2& velocity) {
 velocity_ = velocity;
 return velocity_;
}

}// namespace particle

}// namespace idealgas
