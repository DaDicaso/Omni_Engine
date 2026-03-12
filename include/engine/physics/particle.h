#pragma once

#include <engine/math/vector3.h>

namespace engine {
  class Particle {
  public:
    // Keeps track of linear world position.
    Vector3 position;

    // Keeps track of linear velocity of the particle in world space.
    Vector3 velocity;

    // Keeps track of acceleration of particle.
    // This value can be set to acceleration due to gravity
    // or any other constant acceleration.
    Vector3 acceleration;

    // Accumulated force to apply during integration.
    Vector3 forceAccum;

    // Amount of damping applied to linear motion.
    // Damping removes energy added through numerical instability in the integrator.
    real damping;

    // Inverse mass of the particle.
    real inverseMass;

    void integrate(real duration);

    /*
    * Clears the forces applied to the particle. This will be called automatically after each integration step.
    */
   void clearAccumulator();

   /*
   * Adds the given force to the particle, to be applied at the next iteration only.
   * @param force The force to apply.
   */
  void addForce(const Vector3 &force);
  };
}  // namespace engine
