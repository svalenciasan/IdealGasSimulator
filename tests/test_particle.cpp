#include <catch2/catch.hpp>

#include <core/particle.h>
using idealgas::particle::Particle;

TEST_CASE("Update", "[update]") {
    SECTION("Update <0,0> velocity") {
    vec2 position(0,0);
    vec2 velocity(0,0);
    Particle particle(10, position, velocity);
    particle.Update();
    REQUIRE(particle.GetPosition() == vec2(0,0));
    }
  SECTION("Update <0,1> velocity") {
    vec2 position(0,0);
    vec2 velocity(0,1);
    Particle particle(10, position, velocity);
    particle.Update();
    REQUIRE(particle.GetPosition() == vec2(0,1));
  }
  SECTION("Update <1,0> velocity") {
    vec2 position(0,0);
    vec2 velocity(1,0);
    Particle particle(10, position, velocity);
    particle.Update();
    REQUIRE(particle.GetPosition() == vec2(1,0));
  }
  SECTION("Update <1,1> velocity") {
    vec2 position(0,0);
    vec2 velocity(1,1);
    Particle particle(10, position, velocity);
    particle.Update();
    REQUIRE(particle.GetPosition() == vec2(1,1));
  }
  //Negative
  SECTION("Update <0,-1> velocity") {
    vec2 position(0,0);
    vec2 velocity(0,-1);
    Particle particle(10, position, velocity);
    particle.Update();
    REQUIRE(particle.GetPosition() == vec2(0,-1));
  }
  SECTION("Update <-1,0> velocity") {
    vec2 position(0,0);
    vec2 velocity(-1,0);
    Particle particle(10, position, velocity);
    particle.Update();
    REQUIRE(particle.GetPosition() == vec2(-1,0));
  }
  SECTION("Update <-1,-1> velocity") {
    vec2 position(0,0);
    vec2 velocity(-1,-1);
    Particle particle(10, position, velocity);
    particle.Update();
    REQUIRE(particle.GetPosition() == vec2(-1,-1));
  }
}