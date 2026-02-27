#include "vector3.h"

namespace engine
{
  class Particle{
  public:
    // Keeps track of linear world position
    Vector3 position;

    // Keeps track of linear velocity of the particle in world space
    Vector3 velocity;

    // Keeps track of acceleration of particle. 
    // This value can be set to acc. due to gravity or any other const acc.
    Vector3 acceleration;
    
    Vector3 forceAccum;

    //Holds the amount of damping applied to linear motion.
    //Damping is required to remove energy added through numerical instability in the intergrator
    real damping;

    //Holds the inrvese of the mass of the particle
    real inverseMass;

    void integrate(real duration);
  };
}