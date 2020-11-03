#include <visualizer/sketchpad.h>
#include "core/particle_manager.h"
#include <sstream>

using idealgas::particlemanager::ParticleManager;

namespace idealgas {

namespace visualizer {

using glm::vec2;
using std::stringstream;

Sketchpad::Sketchpad(const vec2& top_left_corner, size_t num_pixels_per_side,
                     double sketchpad_size)
    : top_left_corner_(top_left_corner),
      num_pixels_per_side_(num_pixels_per_side),
      pixel_side_length_(sketchpad_size / num_pixels_per_side) {
  vec2 bottom_right_corner = top_left_corner_ + vec2(num_pixels_per_side_ * pixel_side_length_, num_pixels_per_side_ * pixel_side_length_);
  particleManager_ = ParticleManager(top_left_corner_, bottom_right_corner);
}
Sketchpad::Sketchpad() {}

void Sketchpad::Update() {
  particleManager_.CheckBarrierCollisions();
  particleManager_.CheckParticleCollisions();
  particleManager_.Update();
}

void Sketchpad::Draw() const {
  vec2 pixel_bottom_right = top_left_corner_ + vec2(num_pixels_per_side_ * pixel_side_length_, num_pixels_per_side_ * pixel_side_length_);
  ci::Rectf pixel_bounding_box(top_left_corner_, pixel_bottom_right);

  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(pixel_bounding_box);

  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box);

  for (Particle particle : particleManager_.GetParticles()) {
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
}

void Sketchpad::Clear() {
  particleManager_.ClearParticles();
}

void Sketchpad::AddParticle(float radius, vec2 position, vec2 velocity) {
  Particle particle(radius, position, velocity);
  particleManager_.AddParticle(particle);
}
}  // namespace visualizer

}  // namespace naivebayes
