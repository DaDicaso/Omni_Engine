#pragma once
#include<engine/scenes/scenes.h>
#include<engine/physics/particle.h>
#include<engine/constraints/plinks.h>
#include<vector>

struct BridgeScene : public Scenes
{
  std::vector<engine::Particle> particles;
  std::vector<engine::ParticleRod> rods;
  std::vector<engine::ParticleCable> cables;
  std::vector<engine::Particle> topParticles;

  void init() override;
  void update(float dt) override;
  void render() override;
  void reset() override;

  void generateContacts(engine::ParticleContact *contacts, int& count);

  engine::Particle* getClosestParticle(const engine::Vector3& pos);
};
