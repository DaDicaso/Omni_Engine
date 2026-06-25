#include<engine/physics/pworld.h>

using namespace engine;

void ParticleWorld::startFrame(){
  ParticleRegistration *reg = firstParticle;
  while(reg){
     
    //Remove all forces from the accumulator
    reg->particle->clearAccumulator();

    //Get the next registration
    reg = reg->next;
  }
}
unsigned ParticleWorld::generateContacts(){
  unsigned limit = maxContacts;
  ParticleContact *nextContact = contacts;

  ContactGenRegistration *reg = firstContactGen;

  while(reg){
    unsigned used = reg->gen->addContact(nextContact, limit);
    limit -= used;
    nextContact += used;

    // We've run out of contacts to fill. This means we're missing contacts.
    if(limit < 0) break;

    reg = reg->next;
  }

  // Return the number of contacts used.
  return maxContacts - limit;
}

void ParticleWorld::integrate(real duration){
  ParticleRegistration *reg = firstParticle;
  while(reg){
    // Remove all forces from the accumulator
    reg->particle->integrate(duration);

    // Get the next registration
    reg = reg->next;
  }
}

void ParticleWorld::runPhysics(real duration){
  // First apply the force generators
  registry.updateForces(duration);

  // Then integrate the obejcts.
  integrate(duration);

  // Generate contacts
  unsigned usedContacts = generateContacts();

  // And Process them
  if(calculateIterations) resolver.setIterations(usedContacts * 2);
  resolver.resolveContacts(contacts, usedContacts, duration);
}

