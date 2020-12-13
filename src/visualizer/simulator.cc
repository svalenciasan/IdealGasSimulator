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

ParticleManager Simulator::Update() {
  particleManager_.CheckBarrierCollisions();
  particleManager_.CheckParticleCollisions();
  particleManager_.Update();
  return particleManager_;
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

Particle& Simulator::AddParticle(float radius, float mass, vec2 position, vec2 velocity) {
  Particle particle(radius, mass, position, velocity);
  particleManager_.AddParticle(particle);
  return particleManager_.GetParticles().back();
}

Particle& Simulator::AddParticle(float radius, float mass, vec2 position, vec2 velocity, string color) {
  Particle particle(radius, mass, position, velocity);
  particle.SetColor(color);
  particleManager_.AddParticle(particle);

//  if (color == "black") {
//    //particleManager_.GetParticles().back()
//    firstHistogram_.AddParticle(particleManager_.GetParticles().back());
//  } else if (color == "blue") {
//    secondHistogram_.AddParticle(particleManager_.GetParticles().back());
//  } else if (color == "red") {
//    secondHistogram_.AddParticle(particleManager_.GetParticles().back());
//  }
  return particleManager_.GetParticles().back();
}
}  // namespace visualizer

}  // namespace naivebayes
