#pragma once

#include "cinder/gl/gl.h"

using std::string;
using glm::vec2;

namespace idealgas {

namespace particle {
    class Particle {
    public:
        //Constructors
        Particle();
        Particle(float radius, vec2 position, vec2 velocity);
        //Functions
        void Update();

        //Getters-Setters
        vec2 GetVelocity();
        vec2 GetPosition();
        vec2 SetVelocity(vec2 position);
        vec2 SetPosition(vec2 velocity);
    private:
        constexpr static const float kDefaultXPos = 0;
        constexpr static const float kDefaultYPos = 0;
        constexpr static const float kDefaultXVelocity = 1;
        constexpr static const float kDefaultYVelocity = 1;

        const float kRadius;

        vec2 position_;
        vec2 velocity_;
    };
}//namespace particle

}//namespace ideal_gas