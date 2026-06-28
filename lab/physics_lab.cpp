#include "lab/physics_lab.h"

#include<iostream>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

namespace omni{

  PhysicsLab::PhysicsLab() : mRenderer(mWindow){

  }

  PhysicsLab::~PhysicsLab(){
    
  }

  bool PhysicsLab::initialize(){
    if(!mWindow.create(1200, 720, "Omni Physics Lab")){
      return false;
    }

    mRenderer.initialize();

    mExperimentManager.initialize();

    return true;
  }

  void PhysicsLab::run(){
    if(!initialize()){
      return;
    }

    while(!mWindow.shouldClose()){

      //std::cout << "Runnin... " << std::endl;

      mTime.update();

      mRenderer.beginFrame();

      mExperimentManager.update(mTime.getDeltaTime());

      mExperimentManager.render(mRenderer);

      mRenderer.endFrame();

      mWindow.pollEvents();
    }

    //std::cout << "Window closed." << std::endl;
  }
}