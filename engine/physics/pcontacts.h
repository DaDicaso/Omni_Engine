#pragma once
#include<engine/physics/particle.h>
/*
The contact has no callable function, it just holds the contact details
To resolve a set of contacts, use the particle contact resolver class
*/
namespace engine{
  class ParticleContact{
  public:
    /*
    Holds the particles that are involved in the contact.
    The second of these can be null
    */
    Particle* particle[2];

    // Holds the normal restitution coefficient at the contact
    real restitution;

    // Holds the direction of the contact in world corrdinates.
    Vector3 contactNormal;

    // Holds the depth of penetration at the contact.
    real penetration;
    
    // Calculate the sperating velocity at the contact.
    real calculateSeparatingVelocity() const;
    
    // Resolves this contact for both velocity and inter penetration.
    void resolve(real duration);

  private:
    // Handles the impulse calculation for this collision
    void resolveVelocity(real duration);
  };

  
  /*
    Contact Resolution for particle contacts.
    One resolver instance can be shared for the whole simulation
  */
  
  class ParticleContactResolver{
    // Holds the number of iterations allowed
    real maxIterations;
  
    /*
      This is a performace tracking value - we keep a record of the actual number of 
      iterations used. 
    */
    unsigned iterationsUsed;
  
  public:
    // Creates new contact resolver.
    ParticleContactResolver(unsigned iterations);
  
    // Set the number of iterations that can be used.
    void setIterations(unsigned iterations);
  
    //Resolve a set of particle contacts for both penetration and velocity
    void resolveContacts(ParticleContact *contactArray, unsigned numContacts, real duration);
  };

  class ParticleContactGenerator{
    public:
      /**
       * Fills the given contact structure with the generated contact.
       * The contact pointer should point to the first available contact in a contact array, where limit is the max number of contacts in the array that can be written to.
       * The method returns the numbner of contacts that have been written.
       */

       virtual unsigned addContact(ParticleContact *contact, unsigned limit) const = 0;
  };
}
