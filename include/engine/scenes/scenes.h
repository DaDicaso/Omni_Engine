#pragma once
#include<engine/physics/pcontacts.h>

struct Scenes
{
  virtual ~Scenes() {}

  //Called onces when scene starts
  virtual void init() = 0;
  
  // Called every frame
  virtual void update(float dt) = 0;

  // Draw everything
  virtual void render() = 0;

  // Reset scene state
  virtual void reset() = 0;

  virtual void generateContacts(engine::ParticleContact*, int&) {}
};
