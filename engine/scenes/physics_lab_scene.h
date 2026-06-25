#pragma once

#include<engine/physics/pworld.h>

namespace engine{
  class PhysicsLabScene{
    public:
      PhysicsLabScene();

      void init();
      void update(float dt);
      void render();

    private:
      ParticleWorld world;
  };
}