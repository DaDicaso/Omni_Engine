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

void Particle::setPosition(real x, real y, real z){
  position.x = x;
  position.y = y;
  position.z = z;
}

void Particle::setVelocity(real x, real y, real z){
  velocity.x = x;
  velocity.y = y;
  velocity.z = z;
}

void Particle::setAcceleration(real x, real y, real z){
  acceleration.x = x;
  acceleration.y = y;
  acceleration.z = z;
}

void Particle::setMass(real mass){
  assert(mass != 0);
  inverseMass = ((real)1.0)/mass;
}

void Particle::setDamping(real d){
  damping = d;
}

Vector3 Particle::getPosition(){
  return position;
}

Vector3 Particle::getVelocity(){
  return velocity;
}

void Particle::getVelocity(Vector3 *velocity) const{
  *velocity = this->velocity;
}

Vector3 Particle::getAcceleration(){
  return acceleration;
}

real Particle::getMass(){
  return ((real)1.0/inverseMass);
}

real Particle::getDamping(){
  return damping;
}

bool Particle::hasFiniteMass() const{
  return inverseMass > 0.0f;
}