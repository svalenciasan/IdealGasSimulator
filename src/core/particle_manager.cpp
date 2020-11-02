#include "core/particle_manager.h"
#include "core/particle.h"

using idealgas::particle::Particle;

namespace idealgas {
namespace particlemanager {
    /**
     * Constructors
     */
    ParticleManager::ParticleManager() {

    }
    ParticleManager::ParticleManager(vector<Particle> particles) {
        particles_ = particles;
    }
    /**
     * Functions
     */
     vector<Particle> ParticleManager::Update() {

         for(Particle particle : particles_) {
             particle.Update();
         }
         return particles_;
     }
    /**
     * Getters-Setters
     */
     vector<Particle> ParticleManager::GetParticles() {
         return particles_;
     }
     size_t ParticleManager::GetNumberOfParticles() {
         return number_of_particles_;
     }
}// namespace particle
}// namespace idealgas
