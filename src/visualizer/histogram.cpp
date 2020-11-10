#define _USE_MATH_DEFINES

#include "visualizer/histogram.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "core/particle.h"
#include "core/particle_manager.h"
#include "cmath"
#include <vector>
#include <map>

#include "core/particle.h"

using idealgas::particle::Particle;
using glm::length;

namespace idealgas {

namespace visualizer {
Histogram::Histogram(const vec2 &top_left_corner,
                     const vec2 &bottom_right_corner,
                     size_t num_of_rectangles) :
      kTopLeftCorner(top_left_corner),
      kBottomRightCorner(bottom_right_corner){
  num_of_rectangles_ = num_of_rectangles;
  rectangle_width_ = (bottom_right_corner.x - top_left_corner.x - 2 * kMargin) / num_of_rectangles;
}

void Histogram::Update(const ParticleManager& particleManager, string color) {
  particles_.clear();
  color_ = color;
  for (Particle& particle : particleManager.GetParticles()) {
    if (particle.GetColor() == color) {
      AddParticle(particle);
    }
  }
}

void Histogram::Draw() {
  ci::Rectf pixel_bounding_box(kTopLeftCorner, kBottomRightCorner);

  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(pixel_bounding_box);

  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box);

  DrawAxisLabels();

  if (particles_.empty()) {
    return;
  }

  //lower_bound value for speed range
  float lower_bound = 0;
  //higher_bound value for speed range
  float higher_bound = partitions_;

  //Drawing variables
  float left_x_coord = kTopLeftCorner.x + kMargin;
  float bottom_y_coord = kBottomRightCorner.y - kMargin;

  for (size_t column = 1; column <= num_of_rectangles_; column++) {
    //Getting the particles in a category
    size_t particles_in_range = GetNumberInRange(lower_bound, higher_bound);
    float percentage_of_particles = static_cast<float>(particles_in_range) / static_cast<float>(particles_.size());

    //Drawing rectangle
    float height_of_rectangle = (kBottomRightCorner.y - kMargin) - (((kBottomRightCorner.y - kMargin) - (kTopLeftCorner.y + kMargin)) * percentage_of_particles);
    vec2 top_left(left_x_coord, height_of_rectangle);
    vec2 bottom_right(left_x_coord + rectangle_width_, bottom_y_coord);

    //Drawing rectangle on app
    ci::Rectf bounds(top_left, bottom_right);
    ci::gl::color(ci::Color(color_.c_str()));
    ci::gl::drawSolidRect(bounds);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRect(pixel_bounding_box);

    //Speed range update
    lower_bound = higher_bound;
    higher_bound += partitions_;
    //Left bound for rectangle update
    left_x_coord += rectangle_width_;
  }
}

void Histogram::DrawAxisLabels() {
  float length = kBottomRightCorner.x - kTopLeftCorner.x;
  float half_length = length / 2;

  float height = kBottomRightCorner.y - kTopLeftCorner.y;
  float half_height = height / 2;
  //X-axis
  ci::gl::drawStringCentered(
      "Particle speed",
      vec2(kBottomRightCorner.x - half_length, kBottomRightCorner.y - (kMargin / 2)),
      ci::Color(color_.c_str()));


  ci::gl::rotate( (float)-M_PI_2);

  // ci::gl::drawStringCentered(
  //                    "Particle number",
  //                    glm::vec2(-(int) length_ / 2, 0) - vec2(top_left_corner.y, top_left_corner.x),
  //                    ci::Color("black"));
  vec2 position = vec2(-(int) half_height, 0) - vec2(kTopLeftCorner.y, kTopLeftCorner.x);
  position = vec2(position.x, position.y * -1);
  ci::gl::drawStringCentered(
      "Particle number",
      position,
      ci::Color(color_.c_str()));

  ci::gl::rotate((float)M_PI_2);
}

void Histogram::AddParticle(Particle& particle) {
  float particle_velocity = length(particle.GetVelocity());

  if (particle_velocity > highest_vel_) {
    highest_vel_ = particle_velocity;
    partitions_ = highest_vel_ / num_of_rectangles_;
  } else if (particle_velocity < lowest_vel_) {
    lowest_vel_ = particle_velocity;
  }

  particles_.push_back(particle);
}

size_t Histogram::GetNumberInRange(float min, float max) {
  size_t count = 0;
  for (Particle& particle : particles_) {
    float particle_velocity = length(particle.GetVelocity());

    if (particle_velocity >= min && particle_velocity < max) {
      count++;
    }
  }
  return count;
}
}// namespace histogram

}// namespace idealgas