#include<assert.h>
#include <engine/physics/particle.h>

using namespace engine;

void Particle::integrate(real duration){
  assert(duration > 0.0);

  //Update linear position
  position.addScalerVector(velocity, duration);

  //Work out the acceleration from the force
  Vector3 resultingAcc = acceleration;
  resultingAcc.addScalerVector(forceAccum, inverseMass);
  

  //Update linear velocity from acceleration
  velocity.addScalerVector(resultingAcc, duration);

  //Impose Drag
  velocity *= real_pow(damping, duration);

  // Clear the forces.
  clearAccumulator();
}

void Particle::clearAccumulator(){
  forceAccum.clear();
}

void Particle::addForce(const Vector3 &force){
  forceAccum += force;
}