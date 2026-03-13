#include<engine/physics/particle.h>
#include<vector>

namespace engine{
  class ParticleForceGenerator{
    public:
      /*
      * Overload this implementation of the interface to calculate 
      * and update the force applied to the given particle.
      */
      virtual void updateForce(Particle *particle, real duration) = 0;
  };

  // Holds all the forces generators and the particles they apply to.

  class ParticleForceRegistry{
    protected:
      /*
      * Keep track of one force generator and the particle it's applied to.
      */
     struct ParticleForceRegistration
     {
      Particle *particle;
      ParticleForceGenerator *fg;
     };

     // Holds the list of registrations.
     typedef std::vector<ParticleForceRegistration> Registry;
     Registry registrations;

     public:
      
     // Registers the given force generators to apply to the given particle.
     void add(Particle *particle, ParticleForceGenerator *fg);

     /*
     * Removes the given registered pair from the registry.
     * If the pair is not registered, this method will hace no effect
     */
     void remove(Particle* particle, ParticleForceGenerator *fg);

     /*
     * Clears all registrations from the registry. This will not delete the particle or the force generators themselves,
     * just the records of their connection.
     */

     void clear();


     /*
     * calls all the foce generators to update the forces of their corresponding particles.
     */
    void updateForces(real duration);  
  };

  class ParticleGravity : public ParticleForceGenerator{

    // Holds the acc due to gravity
    Vector3 gravity;

    public:
      // Creates the generator with the given acceleration
      ParticleGravity(const Vector3 &gravity);

      // Applies the gravitational force to the given particle
      virtual void updateForce(Particle *particle, real duration);
  };


  // A force generator that applies a drag force. Once instanace can be used for multiple particles
  class ParticleDrag : public ParticleForceGenerator{

    // Holds the velocity draag
    real k1;

    // Holds the velocity squared drag.
    real k2;

    public:
      
      // Creates generator with the given coefficients.
      virtual void updateForce(Particle *particle, real duration);
  };
}