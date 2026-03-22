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

  class ParticleSpring : public ParticleForceGenerator{
    
    // The particle at the other end
    Particle *other;

    // Holds spring constant
    real springConstant;

    // Holds the rest length of the spring
    real restLength;

    public:

      // Creates a new spring with given parameters
      ParticleSpring(Particle *other, real springConstant, real restLength);

      // Applies the spring force to the given particle
      virtual void updateForce(Particle *particle, real duration);
  };

  class ParticleAnchoredSpring : public ParticleForceGenerator{

    // The location of the anchored end of the spring
    Vector3 *anchor;

    // Holds the spring constant
    real springConstant;

    // Holds the rest length of the spring
    real restLength;

    public:
      // Creates a new spring with given parameters
      ParticleAnchoredSpring(Particle *other, real springConstant, real restLength);

      // Applies the spring force to the given particle
      virtual void updateForce(Particle *particle, real duration);
  };

  class ParticleBungee : public ParticleForceGenerator{

    // Particle at the other end of the spring
    Particle *other;

    // Holds the spring constant
    real springConstant;

    // Holds the length of the bungee at the point it begins to generate a force
    real restLength;

    public:
      ParticleBungee(Particle *other, real springConstat, real restLength);

      
      virtual void updateForce(Particle *Particle, real duration);
  };

  class ParticleBuoyancy : public ParticleForceGenerator{
    
    // Maximum submersion depth of the object before it generates its maximum bouyancy
    real maxDepth;

    // The volume of the Obejct
    real volume;

    // The height of the water plane above y = 0. The plane will be parallel to XZ plane
    real waterHeight;
    
    // The density of the liquid. Pure water has a density of 1000kg per cubic meter.
    real liquidDensity;

    public:
      ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity = 1000.0f);

      virtual void updateForce(Particle *Particle, real duration);
  };
  /*
    A force generator that fakes a stiff spring force, and where one end is attached to a fixed point in space.
  */
  
  class ParticleFakeSpring : public ParticleForceGenerator{
  
    //The location of the anchored end of the spring.
    Vector3 *anchor;
  
    //Holds the spring constant
    real springConstant;
  
    // Holds the damping of the oscillation of the spring.
    real damping;
  
  public:
      ParticleFakeSpring(Vector3 *anchor, real springConstant, real damping);
  
      virtual void updateForce(Particle *particle, real duration);
  };
}
