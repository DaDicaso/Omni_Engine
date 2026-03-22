#pragma once

#include <engine/math/vector3.h>

namespace engine {
  class Particle {

  protected:
    Vector3 position; // Keeps track of linear world position.
    Vector3 velocity; // Keeps track of linear velocity of the particle in world space.
    // Keeps track of acceleration of particle.
    // This value can be set to acceleration due to gravity
    // or any other constant acceleration.
    Vector3 acceleration;
    Vector3 forceAccum;   // Accumulated force to apply during integration.

    // Amount of damping applied to linear motion.
    // Damping removes energy added through numerical instability in the integrator.
    real damping;
    real inverseMass; // Inverse mass of the particle.
  public:
    
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

  // All setter methods
  void setPosition(real x, real y, real z);
  void setVelocity(real x, real y, real z);
  void setAcceleration(real x, real y, real z);
  
  void setMass(real mass);
  void setDamping(real damping);
  

  // All getter Methods
  Vector3 getPosition();
  Vector3 getVelocity();

  Vector3 getAcceleration();
  real getMass();
  real getDamping();

  // Write the velocity to the parameter variable.
  void getPosition(Vector3 *position) const;
  void getVelocity(Vector3 *velocity) const;
  
  // Check for finite mass
  bool hasFiniteMass() const;

  };
}