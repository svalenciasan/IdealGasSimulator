#pragma once

#include "cinder/gl/gl.h"
#include "core/particle_manager.h"
#include "core/particle.h"

using std::string;
using glm::vec2;
using idealgas::particle::Particle;
//using idealgas::particlemanager::ParticleManager;

namespace idealgas {

namespace container {

class Container {
 public:
  //Constructors
  Container(size_t height, size_t length);
  //Functions

  //Getters-Setters
  size_t GetHeight() const;
  size_t GetLength() const;

 private:
  size_t height_;
  size_t length_;
};

}//namespace container

}//namespace idealgas