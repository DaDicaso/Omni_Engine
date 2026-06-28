#pragma once

#include "engine/core/window.h"
#include "engine/renderer/renderer.h"
#include "lab/experiment_manager.h"
#include "engine/core/time.h"

struct GLFWwindow;

namespace omni{
  class PhysicsLab{

    public:
    PhysicsLab();
    ~PhysicsLab();
    void run();

  private:  
    bool initialize();

  private:
    Window mWindow;
    Renderer mRenderer;
    ExperimentManager mExperimentManager;
    Time mTime;
    
  };
}