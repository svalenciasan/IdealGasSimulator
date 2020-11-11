#include <catch2/catch.hpp>
#include "core/particle_manager.h"
#include "visualizer/histogram.h"

using idealgas::visualizer::Histogram;

TEST_CASE("Get number in range", "[numberinrange]") {
  ParticleManager particleManager(vec2(0,0), vec2(200, 200));
  float radius = 5;
  float mass = 10;
  vec2 position(50, 50);
  vec2 velocity(2,1);

  Histogram histogram;
  SECTION("No particles") {
    REQUIRE(histogram.GetNumberInRange(0, 999) == 0);
  }

  SECTION("One particle") {
    particleManager.ClearParticles();
    Particle particle(radius, mass, position, velocity);
    particleManager.AddParticle(particle);
    histogram.Update(particleManager, "black");
    REQUIRE(histogram.GetNumberInRange(0, static_cast<float>(sqrt(6))) == 1);
  }

  SECTION("Multiple particle") {
    particleManager.ClearParticles();
    //Adding 10 particles
    for (int index = 0; index < 4; index++) {
      if (index % 2 == 0) {
        Particle particle(radius, mass, position, velocity);
        particleManager.AddParticle(particle);
      } else {
        velocity = vec2(velocity.x + index % 2, velocity.y + index % 2);
        Particle particle(radius, mass, position, velocity);
        particleManager.AddParticle(particle);
      }
    }
    histogram.Update(particleManager, "black");
    //21 32 32 43
    REQUIRE(histogram.GetNumberInRange(0, static_cast<float>(2.237)) == 1);
    REQUIRE(histogram.GetNumberInRange(static_cast<float>(2.237), static_cast<float>(3.61)) == 2);
    REQUIRE(histogram.GetNumberInRange(static_cast<float>(3.61), static_cast<float>(6)) == 1);
  }
}