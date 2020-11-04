#include <catch2/catch.hpp>
#include <core/particle.h>
#include <core/particle_manager.h>

using idealgas::particle::Particle;
using idealgas::particlemanager::ParticleManager;

TEST_CASE("Update particle manager", "[update][particlemanager]") {
  vec2 topLeftCorner(0,0);
  vec2 topRightCorner(100,100);
  ParticleManager particleManager(topLeftCorner, topRightCorner);
  SECTION("Empty list") {
    particleManager.Update();
    REQUIRE(particleManager.GetParticles().size() == 0);
  }
  SECTION("Single item list") {
    vec2 position(0,0);
    vec2 velocity(1,1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);
    particleManager.Update();
    REQUIRE(particleManager.GetParticles().size() == 1);
    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(1,1));
  }
  SECTION("Two item list") {
    vec2 position(0,0);
    vec2 velocity(1,1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    vec2 position2(2,2);
    vec2 velocity2(2,2);
    Particle particle2(10, position2, velocity2);
    particleManager.AddParticle(particle2);

    particleManager.Update();
    REQUIRE(particleManager.GetParticles().size() == 2);
    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(1,1));
    REQUIRE(particleManager.GetParticles().at(1).GetPosition() == vec2(4,4));
  }
}

TEST_CASE("Check barrier collision", "[checkbarriercollision]") {
  vec2 topLeftCorner(0,0);
  vec2 topRightCorner(100,100);
  ParticleManager particleManager(topLeftCorner, topRightCorner);
  SECTION("Empty list") {
    particleManager.CheckBarrierCollisions();
    REQUIRE(particleManager.GetParticles().size() == 0);
  }
  SECTION("Single item list in bounds") {
    vec2 position(20,20);
    vec2 velocity(1,1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == particle.GetVelocity());

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == particle.GetPosition());
  }
  SECTION("Two item list in bounds") {
    vec2 position(20,20);
    vec2 velocity(1,1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    vec2 position2(2,2);
    vec2 velocity2(2,2);
    Particle particle2(10, position2, velocity2);
    particleManager.AddParticle(particle2);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 2);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == particle.GetVelocity());
    REQUIRE(particleManager.GetParticles().at(1).GetVelocity() == particle2.GetVelocity());

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == particle.GetPosition());
    REQUIRE(particleManager.GetParticles().at(1).GetPosition() == particle2.GetPosition());
  }
  //Top out of bounds
  SECTION("Not in top bounds but correct y velocity") {
    vec2 position(20,-1);
    vec2 velocity(1,1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(1,1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(20,-1));
  }
  SECTION("Not in top bounds and incorrect y velocity") {
    vec2 position(20,-1);
    vec2 velocity(1,-1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(1,1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(20,-1));
  }
  //Bottom out of bounds
  SECTION("Not in bottom bounds but correct y velocity") {
    vec2 position(20,102);
    vec2 velocity(1,-1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(1,-1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(20,102));
  }
  SECTION("Not in bottom bounds and incorrect y velocity") {
    vec2 position(20,102);
    vec2 velocity(1,1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(1,-1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(20,102));
  }
  //Left out of bounds
  SECTION("Not in left bounds but correct x velocity") {
    vec2 position(-1,20);
    vec2 velocity(1,-1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(1,-1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(-1,20));
  }
  SECTION("Not in left bounds and incorrect x velocity") {
    vec2 position(-1,20);
    vec2 velocity(-1,-1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(1,-1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(-1,20));
  }
  //Right out of bounds
  SECTION("Not in right bounds but correct x velocity") {
    vec2 position(102,20);
    vec2 velocity(-1,-1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(-1,-1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(102,20));
  }
  SECTION("Not in right bounds and incorrect x velocity") {
    vec2 position(102,20);
    vec2 velocity(1,-1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(-1,-1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(102,20));
  }
  //Not in top-left bounds
  SECTION("Not in both top left bounds but correct x and y velocity") {
    vec2 position(-1,-1);
    vec2 velocity(1,1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(1,1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(-1,-1));
  }
  SECTION("Not in both top left bounds and incorrect x and y velocity") {
    vec2 position(-1,-1);
    vec2 velocity(-1,-1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(1,1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(-1,-1));
  }
  SECTION("Not in both top left bounds and incorrect x velocity") {
    vec2 position(-1,-1);
    vec2 velocity(-1,1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(1,1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(-1,-1));
  }
  SECTION("Not in both top left bounds and incorrect y velocity") {
    vec2 position(-1,-1);
    vec2 velocity(1,-1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(1,1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(-1,-1));
  }
  //Not in bottom-right bounds
  SECTION("Not in both bottom right bounds but correct x and y velocity") {
    vec2 position(101,101);
    vec2 velocity(-1,-1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(-1,-1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(101,101));
  }
  SECTION("Not in both bottom right bounds and incorrect x and y velocity") {
    vec2 position(101,101);
    vec2 velocity(1,1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(-1,-1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(101,101));
  }
  SECTION("Not in both bottom right bounds and incorrect x velocity") {
    vec2 position(101,101);
    vec2 velocity(1,-1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(-1,-1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(101,101));
  }
  SECTION("Not in both bottom right bounds and incorrect y velocity") {
    vec2 position(101,101);
    vec2 velocity(-1,1);
    Particle particle(10, position, velocity);
    particleManager.AddParticle(particle);

    particleManager.CheckBarrierCollisions();

    REQUIRE(particleManager.GetParticles().size() == 1);

    REQUIRE(particleManager.GetParticles().at(0).GetVelocity() == vec2(-1,-1));

    REQUIRE(particleManager.GetParticles().at(0).GetPosition() == vec2(101,101));
  }
}

