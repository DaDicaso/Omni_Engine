#pragma once

struct GLFWwindow;

namespace omni{
  class PhysicsLab{

    public:
    PhysicsLab();
    ~PhysicsLab();
    void run();

  private:  
    bool initialize();
    void shutdown();

  private:
    GLFWwindow* mWindow = nullptr;
    
  };
}