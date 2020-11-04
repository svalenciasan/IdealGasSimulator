#pragma once

#include "cinder/gl/gl.h"

using std::string;
using glm::vec2;

namespace idealgas {

namespace particle {

class Particle {
 public:
  //Constructors
  Particle() = default;
  Particle(float radius, vec2& position, vec2& velocity);
  //Functions
  void Update();

  //Getters-Setters
  vec2 GetVelocity() const;
  vec2 GetPosition() const;
  float GetRadius() const;
  vec2 SetVelocity(const vec2& velocity);
  vec2 SetPosition(const vec2& position);

  private:
  const float kRadius;
  vec2 position_;
  vec2 velocity_;
};

}//namespace particle

}//namespace idealgas