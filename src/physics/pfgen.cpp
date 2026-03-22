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

void ParticleSpring::updateForce(Particle *particle, real duration){

  // Calculate the vector of the Spring.
  Vector3 force;
  particle->getPosition(&force);
  force -= other->getPosition();

  // Calculation magnitude of the force
  real magnitude = force.magnitude();
  magnitude = real_abs(magnitude - restLength);
  magnitude *= springConstant;

  // Calculate the final force to apply
  force.normalize();
  force *= -magnitude;

  particle->addForce(force);
}

void ParticleAnchoredSpring::updateForce(Particle *particle, real duration){
  Vector3 force;
  particle->getPosition(&force);
  force -= *anchor;

  real magnitude = force.magnitude();
  magnitude = real_abs(magnitude - restLength);
  magnitude *= springConstant;

  force.normalize();
  force *= -magnitude;
  particle->addForce(force);
}

void ParticleBungee::updateForce(Particle *particle, real duration){
  Vector3 force;
  particle->getPosition(&force);
  force -= other->getPosition();

  real magnitude = force.magnitude();
  if(magnitude <= restLength) return;

  magnitude = springConstant * (restLength - magnitude);

  force.normalize();
  force *= -magnitude;
  particle->addForce(force);
}

void ParticleBuoyancy::updateForce(Particle *particle, real duration){
  real depth = particle->getPosition().y;

  // Check if the particle is in the water or not?
  if(depth >=waterHeight + maxDepth) return;
  Vector3 force(0, 0, 0);

  // if particle is at maximum depth
  if(depth <= waterHeight - maxDepth){
    force.y = liquidDensity * volume;
    particle->addForce(force);
    return;
  }

  // if the particle is partially submerged
  force.y = liquidDensity * volume * (depth - maxDepth - waterHeight)/ 2 * maxDepth;
  particle->addForce(force);
}

void ParticleFakeSpring::updateForce(Particle *particle, real duration){
  
  // Check if we do not have infinite mass
  if(!particle->hasFiniteMass()) return;

  // Calculate the relative position of the particle to the anchor;
  Vector3 position;
  particle->getPosition(&position);
  position -= *anchor;

  // Calculate the constants and check whether they are in bounds
  real gamma = 0.5f * real_sqrt(4*springConstant - damping * damping);
  if(gamma == 0.0f) return;
  Vector3 c = position * (damping/2.0f * gamma) + particle->getVelocity() * (1.0f/gamma);

  // Calculate the target position
  Vector3 target = position * real_cos(gamma * duration) + c * real_sin(gamma * duration);
  target *= real_exp(-0.5f * damping * duration);

  // Calculate the resulting acceleration and therefore the force
  Vector3 acc = (target - position) * (1.0f/(duration*duration)) - particle->getVelocity() * duration;
  particle->addForce(acc * particle->getMass());
}