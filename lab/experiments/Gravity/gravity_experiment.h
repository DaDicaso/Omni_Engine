#pragma once

#include "lab/experiment.h"
#include "engine/physics/particle.h"

namespace omni{

  class GravityExperiment : public Experiment{
    public:

      GravityExperiment();
      ~GravityExperiment();

      void initialize() override;
      void update(float dt) override;
      void render(Renderer& renderer) override;
      void shutdown() override;

    private:
    
      Particle mParticle;
  };
}