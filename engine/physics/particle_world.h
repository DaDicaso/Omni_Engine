#include<engine/physics/particle.h>
#include<engine/physics/particle_contacts.h>
#include<engine/physics/particle_force_registry.h>

namespace omni{
  /**
   * Keeps track of a set of particles, and provides the means to upda te them all
   */
  class ParticleWorld{

    /**
     * Initialize the world for a simulation frame.
     * This clears the force accumulators for particles for particles in the world.
     * After calling this, the particles can have their forces for this frame added.
     */
    void startFrame();

    // Holds one particle in the linked list of particles.
    struct ParticleRegistration{
      omni::Particle *particle;
      ParticleRegistration *next;
    };

    // Check whether engine should automatically determine how many contact-resolution iterations to use
    bool calculateIterations;

    // Holds the list of registrations.
    ParticleRegistration* firstParticle;
    public:
      /**
       * Creates a new Particle simulator that can handle up to the given number of contact per frame.
       * You can also optimally give a number of contact-resolution Iterations to use.
       * If we don't give a number of iterations, then twice the number of contacts will be used.
       */
      ParticleWorld(unsigned maxContacts, unsigned iterations = 0);

    // Holds the force generators for the particles in this world
    ParticleForceRegistry registry;

    // Holds the resolver for contacts.
    ParticleContactResolver resolver;

    // Holds one registered contact generator.
    struct ContactGenRegistration{
      ParticleContactGenerator *gen;
      ContactGenRegistration *next;
    };

    // Holds the list of contant generators.
    ContactGenRegistration *firstContactGen;

    // Holds the list of contacts.
    ParticleContact *contacts;

    // Holds the maximum number of contacts allowed (i.e., the size of the contact array).
    unsigned maxContacts;


    public:
      /**
       * Calls each of the registered contact generators to report their contacts.
       * Return the number of generated contacts.
       */
      unsigned generateContacts();

      /*
      Integrate all the particles in this world forward in time by the given duration
      */
      void integrate(real duration);

      /*
      Process all the physics for the particle world.
      */
     void runPhysics(real duration);
  };
}

