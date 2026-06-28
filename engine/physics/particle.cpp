#include<assert.h>
#include<iostream>
#include <engine/physics/particle.h>

using namespace omni;

Particle::Particle()
  : position(), velocity(), acceleration(),
  forceAccum(), damping(0.99f), inverseMass(1.0f){

  }

void Particle::integrate(real duration){
  assert(duration > 0.0);
  // std::cout << "Imass: " << inverseMass << '\n';
  // std::cout << "Velocity Y Before: " << velocity.y << '\n';
  // std::cout << "Acceleration Y: " << acceleration.y << '\n';

  // std:: cout << "Integrate particle @ " << this << std::endl;

  // We don't integrate things with zero mass.
  if(inverseMass <= 0.0f) return;

  //Update linear position
  position.addScaledVector(velocity, duration);
  //std::cout << "Position Y: " << position.y << '\n';
  
  //Work out the acceleration from the force
  Vector3 resultingAcceleration = acceleration;
  resultingAcceleration.addScaledVector(forceAccum, inverseMass);
  
  
  //Update linear velocity from acceleration
  velocity.addScaledVector(resultingAcceleration, duration);
  //std::cout << "Velocity Y After: " << velocity.y << '\n';
  
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

void Particle::setPosition(const Vector3& position){
  this->position = position;
}

void Particle::setVelocity(real x, real y, real z){
  velocity.x = x;
  velocity.y = y;
  velocity.z = z;
}

void Particle::setVelocity(const Vector3& velocity){
  this->velocity = velocity;
}

void Particle::setAcceleration(real x, real y, real z){
  acceleration.x = x;
  acceleration.y = y;
  acceleration.z = z;
}

void Particle::setAcceleration(const Vector3& acceleration){
  this->acceleration = acceleration;
}

void Particle::setMass(real mass){
  if(mass <= 0.0f){
    inverseMass = 0;
  }else{
    inverseMass = 1.0f / mass;
  }
}

void Particle::setInverseMass(real inverseMass){
  this->inverseMass = inverseMass;
}

void Particle::setDamping(real d){
  damping = d;
}

const Vector3& Particle::getPosition() const{
  return position;
}

const Vector3& Particle::getVelocity() const{
  return velocity;
}

void Particle::getVelocity(Vector3 *velocity) const{
  *velocity = this->velocity;
}

const Vector3& Particle::getAcceleration() const{
  return acceleration;
}

real Particle::getMass() const{
  if(inverseMass == 0.0f){
    return std::numeric_limits<real>::max(); 
  }

  return 1.0f / inverseMass;
}

real Particle::getInverseMass() const{
  return inverseMass;
}

real Particle::getDamping() const{
  return damping;
}

bool Particle::hasFiniteMass() const{
  return inverseMass > 0.0f;
}