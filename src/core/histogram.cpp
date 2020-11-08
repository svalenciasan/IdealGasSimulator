#include "core/histogram.h"
#include "core/particle.h"

using idealgas::particle::Particle;

namespace idealgas {

namespace histogram {
Histogram::Histogram(const vec2 &top_left_corner,
                     const vec2 &bottom_right_corner,
                     size_t num_of_rectangles) :
      kTopLeftCorner(top_left_corner),
      kBottomRightCorner(bottom_right_corner){
  num_of_rectangles_ = num_of_rectangles;
}

void Histogram::AddParticle(const Particle& particle) {
  float particle_velocity = length(particle.GetVelocity());

  if (particle_velocity > highest_vel_) {
    highest_vel_ = particle_velocity;
  } else if (particle_velocity < lowest_vel_) {
    lowest_vel_ = particle_velocity;
  }

  particles_.push_back(particle);
}

size_t Histogram::GetNumberInRange(float greater_than, float less_than) {
  size_t count = 0;
  for (Particle particle : particles_) {
    float particle_velocity = length(particle.GetVelocity());

    if (particle_velocity > greater_than && particle_velocity < less_than) {
      count++;
    }
  }
  return count;
}
}// namespace histogram

}// namespace idealgas