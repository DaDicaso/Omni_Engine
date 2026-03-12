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
