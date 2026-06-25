#pragma once
#include "scenes.h"
#include <vector>
#include<engine/physics/particle.h>
#include<engine/constraints/plinks.h>
#include<engine/physics/pcontacts.h>


struct RodScene : public Scenes{

  std::vector<engine::Particle> particles;
  std::vector<engine::ParticleRod> rods;

  int selectedParticle = -1;

  void init() override;
  void update(float dt) override;
  void render() override;
  void reset() override;

  void generateContacts(engine::ParticleContact *contacts, int& count);
};