#pragma once

#include "cinder/gl/gl.h"
#include "core/particle.h"
#include <vector>

using std::string;
using std::vector;
using glm::vec2;
using idealgas::particle::Particle;

namespace idealgas {

namespace histogram {

class Histogram {
 public:
  Histogram() = default;
  Histogram(vec2 top_left_corner, vec2 bottom_right_corner);
  void AddParticle(const Particle& particle);
 private:
  vector<Particle> particles;
  vec2 top_left_corner_;
  vec2 bottom_right_corner_;
  size_t num_of_rectangles_;
  float highest_vel_;
  float lowest_vel_;
};

}//namespace particle

}//namespace idealgas