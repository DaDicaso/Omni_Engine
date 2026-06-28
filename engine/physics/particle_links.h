#pragma once
#include<engine/physics/particle.h>
#include<engine/physics/particle_contacts.h>

/*
* Links connect two particles together, generating a contact if they violate the constraints of their link.
* It is used as a base class for cables and rods, and could be used as a base class for springs with a limit to their extension.
*/
namespace omni{
  class ParticleLink{
  public:
    // Holds the pair of particles that are connected by this link
    Particle* particle[2];

    // Returns the current length of the cable.
    real currentLength() const;

  public:
    /**
     * Fills the given contact structure with the contact needed to keep the link from violating its constraint.
     * The contact pointer should point to the first available contact in a contact array, where limit is the maximum number of contacts in the array that can be written to.
     * The method return the number of contacts that have been written.
     * This format is common to contact-generating functions, but this class can only generate a single contact, so the pointer can be a pointer to a single element.
     * The limit parameter is assumed to be at least one, and the return is eeither 0, if the cable wasn't overextended, or one if a contact was needed.
     */

     //virtual unsigned fillContact(ParticleContact *contact, unsigned limit) const = 0;
      virtual unsigned addContact(ParticleContact *contact, unsigned limit) const = 0;
  };

  /**
   * Cables link a pair of particles, generating a contact if they stray too far apart. 
   */
  class ParticleCable : public ParticleLink{
    
  public:
    
    // Holds the maximum length of the cable
    real maxLength;

    // Holds the restitution (bounciness) of the cable
    real restitution;

  public:
    /**
     * Fills the given contact structure with the contact needed to keep the cable from overextending
     */
    //virtual unsigned fillContact(ParticleContact *contact, unsigned limit) const;

    virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
  };

  /**
   * Rods link a pair of particle, generating a contact if they stray too far apart or too close
  */
  class ParticleRod : public ParticleLink{

  public:
    // Holds the length of the rod
    real length;

    real maxStress = 0.5f;
    bool broken = false;

  public:
    /**
     * Fills the given contact structure with the contact needed to keep the rod from extending or compressing 
     */
    //virtual unsigned fillContact(ParticleContact *contact, unsigned limit) const;

    virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
  };
}