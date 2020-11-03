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
  particleManager_ = ParticleManager(num_pixels_per_side, num_pixels_per_side);
}
Sketchpad::Sketchpad() {}

void Sketchpad::Draw() const {
  for (size_t row = 0; row < num_pixels_per_side_; ++row) {
    for (size_t col = 0; col < num_pixels_per_side_; ++col) {
      // TODO: Replace the if-statement below with an if-statement that checks
      // if the pixel at (row, col) is currently shaded
      if ('_' == '#') {
        ci::gl::color(ci::Color::gray(0.3f));
      } else {
        ci::gl::color(ci::Color("white"));
      }

      vec2 pixel_top_left = top_left_corner_ + vec2(col * pixel_side_length_,
                                                    row * pixel_side_length_);

      vec2 pixel_bottom_right =
          pixel_top_left + vec2(pixel_side_length_, pixel_side_length_);
      ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

      ci::gl::drawSolidRect(pixel_bounding_box);

      ci::gl::color(ci::Color("black"));
      ci::gl::drawStrokedRect(pixel_bounding_box);
    }
  }
}

void Sketchpad::Clear() {

}
}  // namespace visualizer

}  // namespace naivebayes
