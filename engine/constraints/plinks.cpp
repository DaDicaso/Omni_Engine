#include<engine/constraints/plinks.h>

using namespace engine;

real ParticleLink::currentLength() const {
    Vector3 relativePos = particle[0]->getPosition() - particle[1]->getPosition();
    return relativePos.magnitude();
}

unsigned ParticleCable::addContact(ParticleContact *contact, unsigned limit) const{
  // If no contacts can be written, return
  if(limit == 0) return 0;

  //Find current length
  real length = currentLength();

  // Check if cable is over-extended
  if(length < maxLength) return 0;

  // Fill the contact structure
  contact->particle[0] = particle[0];
  contact->particle[1] = particle[1];

  // Calculate Normal
  Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();

  real len = normal.magnitude();

  if(len <= 0.0001f) return 0;
  normal.normalize();
  contact->contactNormal = normal;

  //Penetration = how much it exceeded max length
  contact->penetration = length - maxLength;
  contact->restitution = restitution;

  return 1;
}


unsigned ParticleRod::addContact(ParticleContact *contact, unsigned limit) const{
  if(limit == 0) return 0;
  if(broken) return 0;

  real currentLen = currentLength();
  
  //If length is correct, no contact needed
  if(fabs(currentLen - length) < 0.0001f) return 0;

  contact->particle[0] = particle[0];
  contact->particle[1] = particle[1];

  Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();

  real len = normal.magnitude();
  if(len <= 0.0001f) return 0;

  normal.normalize();
  
  if(currentLen > length){
    //Over-extended
    contact->contactNormal = normal;
    contact->penetration = currentLen - length;
  }else{
    // Compressed
    contact->contactNormal = normal * -1;
    contact->penetration = length - currentLen;
  }

  // Rods do not bounce
  contact->restitution = 0;

  return 1;
}

