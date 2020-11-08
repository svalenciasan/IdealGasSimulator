#include <visualizer/simulator.h>

#include <sstream>

using idealgas::particlemanager::ParticleManager;

namespace idealgas {

namespace visualizer {

using glm::vec2;
using std::stringstream;

Simulator::Simulator(const vec2& top_left_corner, const vec2& bottom_right_corner)
    : top_left_corner_(top_left_corner), bottom_right_corner_(bottom_right_corner) {
  particleManager_ = ParticleManager(top_left_corner_, bottom_right_corner);
}
Simulator::Simulator() {}

void Simulator::Update() {
  particleManager_.CheckBarrierCollisions();
  particleManager_.CheckParticleCollisions();
  particleManager_.Update();
}

void Simulator::Draw() const {
  ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner_);

  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(pixel_bounding_box);

  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box);

  for (Particle particle : particleManager_.GetParticles()) {
    string color = particle.GetColor();
    ci::gl::color(ci::Color(color.c_str()));
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
}

void Simulator::Clear() {
  particleManager_.ClearParticles();
}

void Simulator::AddParticle(float radius, float mass, vec2 position, vec2 velocity) {
  Particle particle(radius, mass, position, velocity);
  particleManager_.AddParticle(particle);
}

void Simulator::AddParticle(float radius, float mass, vec2 position, vec2 velocity, string color) {
  Particle particle(radius, mass, position, velocity);
  particle.SetColor(color);
  particleManager_.AddParticle(particle);
}
}  // namespace visualizer

}  // namespace naivebayes
