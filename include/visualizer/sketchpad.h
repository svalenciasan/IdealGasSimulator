#pragma once

#include "cinder/gl/gl.h"

namespace naivebayes {

namespace visualizer {

/**
 * A sketchpad which will be displayed in the Cinder application and respond to
 * mouse events. Furthermore, the sketchpad can output its current state in the
 * same format as the Naive Bayes image data files.
 */
class Sketchpad {
 public:
  Sketchpad(const glm::vec2& top_left_corner, size_t num_pixels_per_side,
            double sketchpad_size);
  Sketchpad();

  /**
   * Displays the current state of the sketchpad in the Cinder application.
   */
  void Draw() const;
  /**
   * Set all of the sketchpad pixels to an unshaded state.
   */
  void Clear();

 private:
  glm::vec2 top_left_corner_;

  size_t num_pixels_per_side_;

  /** Number of screen pixels in the width/height of one sketchpad pixel */
  double pixel_side_length_;
};

}  // namespace visualizer

}  // namespace naivebayes
