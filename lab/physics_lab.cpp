#include "physics_lab.h"

#include<iostream>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

namespace omni{

  PhysicsLab::PhysicsLab(){

  }

  PhysicsLab::~PhysicsLab(){
    shutdown();
  }

  bool PhysicsLab::initialize(){
    if(!glfwInit()){
      std::cerr << "Failed to initiate GLFW\n";
      return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(
      1200,
      720,
      "Omni Physics Lab",
      nullptr, nullptr
    );

    if(!mWindow){
      glfwTerminate();
      return false;
    }

    glfwMakeContextCurrent(mWindow);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
      std::cerr << "Failed to initialize GLAD\n";
      return false;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glViewport(0, 0, 1200, 720);

    return true;
  }

  void PhysicsLab::run(){
    if(!initialize()){
      return;
    }

    while(!glfwWindowShouldClose(mWindow)){

      //std::cout << "Runnin... " << std::endl;


      glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glfwSwapBuffers(mWindow);
      glfwPollEvents();
    }

    //std::cout << "Window closed." << std::endl;
  }

  void PhysicsLab::shutdown(){
    if(mWindow){
      glfwDestroyWindow(mWindow);
      mWindow = nullptr;
    }

    glfwTerminate();
  }
}