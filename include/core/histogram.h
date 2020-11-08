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
  Histogram(const vec2& top_left_corner, const vec2& bottom_right_corner, size_t num_of_rectangles);
  void AddParticle(const Particle& particle);
  size_t GetNumberInRange(float greater_than, float less_than);
 private:
  vector<Particle> particles_;
  const vec2 kTopLeftCorner;
  const vec2 kBottomRightCorner;
  size_t num_of_rectangles_;
  float highest_vel_;
  float lowest_vel_;
};

}//namespace particle

}//namespace idealgas