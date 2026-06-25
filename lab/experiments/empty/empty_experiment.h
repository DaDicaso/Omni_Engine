#pragma once

#include "lab/experiment.h"

namespace omni{

  class EmptyExperiment : public Experiment{
    
    public:
      void init() override;
      void update(float dt) override;
      void render() override;
      void reset() override;
      void shutdown() override;
      const char* getName() const override; 

  };
}