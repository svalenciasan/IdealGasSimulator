#pragma once

#include "cinder/gl/gl.h"
#include "core/particle.h"
#include <vector>

using std::string;
using std::vector;
using glm::vec2;
using idealgas::particle::Particle;

namespace idealgas {
namespace particlemanager {
    class ParticleManager {
    public:
        //Constructor
        ParticleManager();

        ParticleManager(vector<Particle> particles);

        //Functions
        vector<Particle> Update();

        //Getters-Setters
        vector<Particle> GetParticles();

        size_t GetNumberOfParticles();

    private:
        vector<Particle> particles_;
        size_t number_of_particles_;
    };
}//namespace particlemanager
}//namespace ideal_gas
