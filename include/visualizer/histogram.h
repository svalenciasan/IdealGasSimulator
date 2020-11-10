#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "core/particle.h"
#include "core/particle_manager.h"
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;
using glm::vec2;
using idealgas::particle::Particle;
using idealgas::particlemanager::ParticleManager;


namespace idealgas {

namespace visualizer {

class Histogram {
 public:
  Histogram() = default;
  Histogram(const vec2& top_left_corner, const vec2& bottom_right_corner, size_t num_of_rectangles);

  void Update(const ParticleManager& particleManager, string color);
  void Draw();
  void DrawAxisLabels();
  void AddParticle(Particle& particle);
  size_t GetNumberInRange(float greater_than, float less_than);
 private:
  vector<Particle> particles_;
  string color_ = "black";
  const vec2 kTopLeftCorner;
  const vec2 kBottomRightCorner;
  const float kMargin = 20;
  size_t num_of_rectangles_;
  float rectangle_width_;
  //The highest value/number of rectangles
  float partitions_ = 0;
  float highest_vel_ = 0;
  float lowest_vel_ = 0;
};

}//namespace particle

}//namespace idealgas