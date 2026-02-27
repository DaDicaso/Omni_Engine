#include<cassert>
#include<engine/physics/particle.h>

enum ShotType{
  PISTOL,
  ARTILLERTY,
  FIREBALL,
  LASER
};

struct AmmoRound{
  engine::Particle particle;
  ShotType type;
  float startTime;
};

void setShot(AmmoRound* shot, ShotType currentShotType){
  using namespace engine;

  switch (currentShotType)
  {
  case PISTOL:
    shot->particle.setMass(2.0f);
    break;
  
  default:
    break;
  }
}