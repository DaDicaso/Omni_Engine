#include<engine/physics/particle_contacts.h>
#include<iostream>

using namespace omni;

ParticleContactResolver::ParticleContactResolver(unsigned iterations)
    : maxIterations(iterations), iterationsUsed(0) {}

void ParticleContact::resolve(real duration){
  resolveVelocity(duration);
}

real ParticleContact::calculateSeparatingVelocity() const{
  Vector3 relativeVelocity = particle[0]->getVelocity();
  if(particle[1]) relativeVelocity -= particle[1]->getVelocity();
  return relativeVelocity * contactNormal;
}

void ParticleContact::resolveVelocity(real duration){
  real separatingVelocity = calculateSeparatingVelocity();

  if(separatingVelocity > 0){
    /*
    The contact is either separating or stationary - there's no impulse required
    */
    return;
  }

  real newSepVelocity = -separatingVelocity * restitution;

  real deltaVelocity = newSepVelocity - separatingVelocity;
  
  // We apply the change in velocity to each object in proportion to its inverse mass
  real totalInverseMass = particle[0]->getInverseMass();
  if(particle[1]) totalInverseMass += particle[1]->getInverseMass();

  // If all particles have infinite mass, the impulse have no effect
  if(totalInverseMass <= 0) return;

  // Calculate the impulse to apply
  real impulse = deltaVelocity/totalInverseMass;

  // Find the amound of impulse per unit of inverse mass
  Vector3 impulsePerIMass = contactNormal * impulse;

  // Apply impulses: they are applied in the direction of contact and are porportional to the inverse mass
  particle[0]->setVelocity(particle[0]->getVelocity() + impulsePerIMass * particle[0]->getInverseMass());
  
  if(particle[1]){
    // The other particle goes in the opposite direction.
    particle[1]->setVelocity(particle[1]->getVelocity() + impulsePerIMass * -particle[1]->getInverseMass());
  }
}

void ParticleContactResolver::resolveContacts(ParticleContact *contactArray, unsigned numContacts, real duration){
  iterationsUsed = 0;
  while(iterationsUsed < maxIterations){
    //Find the contact with the largest closing velocity;
    real max = 0;
    unsigned  maxIndex = numContacts;

    for(unsigned i = 0; i < numContacts; i++){
      real sepVel = contactArray[i].calculateSeparatingVelocity();

      if(sepVel < max){
        max = sepVel;
        maxIndex = i;
      }
    }

    if(maxIndex == numContacts) break;
    
    // Resolve this contact.
    contactArray[maxIndex].resolve(duration);
    iterationsUsed++;
  }
}

