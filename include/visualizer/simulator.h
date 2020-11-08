#pragma once

#include "cinder/gl/gl.h"
#include "core/particle_manager.h"
#include "core/particle.h"
#include "core/histogram.h"

using idealgas::particle::Particle;
using idealgas::particlemanager::ParticleManager;
using idealgas::histogram::Histogram;
using glm::vec2;

namespace idealgas {

namespace visualizer {

/**
 * A sketchpad which will be displayed in the Cinder application and respond to
 * mouse events. Furthermore, the sketchpad can output its current state in the
 * same format as the Naive Bayes image data files.
 */
class Simulator {
 public:
  Simulator(const vec2& top_left_corner, const vec2& bottom_right_corner);
  Simulator();

  void Update();
  /**
   * Displays the current state of the sketchpad in the Cinder application.
   */
  void Draw() const;
  /**
   * Set all of the sketchpad pixels to an unshaded state.
   */
  void Clear();

  void AddParticle(float radius, float mass, vec2 position, vec2 velocity);
  void AddParticle(float radius, float mass, vec2 position, vec2 velocity, string color);
 private:
  ParticleManager particleManager_;
//  Histogram firstHistogram_;
//  Histogram secondHistogram_;
//  Histogram thirdHistogram_;
  vec2 top_left_corner_;
  vec2 bottom_right_corner_;
  size_t num_pixels_per_side_;
  /** Number of screen pixels in the width/height of one sketchpad pixel */
  double pixel_side_length_;
};

}  // namespace visualizer

}  // namespace naivebayes
