#pragma once

#include "cinder/gl/gl.h"

using std::string;
using glm::vec2;

namespace idealgas {

namespace particle {
    class Particle {
    public:
        Particle(double radius);
        Particle();
        vec2 SetVelocity(double velocity);
        vec2 SetPosition(double position);
    private:
        static const double kDefaultXPos;
        static const double kDefaultYPos;
        static const double kDefaultXVelocity;
        static const double kDefaultYVelocity;
        const double kRadius = 1;

        vec2 position_;
        vec2 velocity_;
    };
}//namespace particle

}//namespace ideal_gas