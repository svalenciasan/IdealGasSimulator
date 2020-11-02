#include "core/particle.h"

namespace idealgas {
namespace particle {
    /**
     * Constructors
     */
    Particle::Particle() : kRadius(10) {
        position_ = vec2 (0,0);
        velocity_ = vec2 (5);
    }
    Particle::Particle(float radius, vec2 position, vec2 velocity) : kRadius(radius) {
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
     vec2 Particle::GetPosition() {
         return position_;
     }
    vec2 Particle::GetVelocity() {
         return velocity_;
     }
    vec2 Particle::SetPosition(vec2 position) {
         position_ = position;
         return position_;
     }
    vec2 Particle::SetVelocity(vec2 velocity) {
         velocity_ = velocity;
         return velocity_;
     }
}// namespace particle
}// namespace idealgas
