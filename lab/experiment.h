#pragma once

namespace omni{
  class Experiment{
    
    public:
      virtual ~Experiment() = default;

      virtual void init() = 0;

      virtual void update(float dt) = 0;

      virtual void render() = 0;
      
      virtual void reset() = 0;

      virtual void shutdown() = 0;

      virtual const char* getName() const = 0;
    
  };
}