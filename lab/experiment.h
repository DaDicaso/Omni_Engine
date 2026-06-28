#pragma once

namespace omni{

  class Renderer;

  class Experiment{
    
    public:
      virtual ~Experiment() = default;

      virtual void initialize() = 0;

      virtual void update(float dt) = 0;

      virtual void render(Renderer& renderer) = 0;

      virtual void shutdown() = 0;

    
  };
}