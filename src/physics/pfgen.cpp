#include<engine/physics/pfgen.h>

using namespace engine;

void ParticleForceRegistry::updateForces(real duration){

  Registry::iterator i = registrations.begin();

  for(; i != registrations.end(); i++){
    i->fg->updateForce(i->particle, duration);
  }
  
}

void ParticleGravity::updateForce(Particle *particle, real duration){

  // Check if we do not have inf mass
  if(!particle->hasFiniteMass()) return;

  // Apply the mass-scaled force to the particle
  particle->addForce(gravity * particle->getMass());
}

void ParticleDrag::updateForce(Particle *particle, real duration){
  Vector3 force;
  particle->getVelocity();

  // Calculate drag from the force;
  real dragCoeff = force.magnitude();
  dragCoeff = k1 * dragCoeff + k2 * dragCoeff*dragCoeff;

  //Calculate final force
  force.normalize();
  force *= -dragCoeff;
  particle->addForce(force);
}