#include "engine/core/window.h"

#include<iostream>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

namespace omni{

  Window::Window(){

  }

  Window::~Window(){
    destroy();
  }

  bool Window::create(int width, int height, const char* title){
    if(!glfwInit()){
      std::cerr << "Failed to initialize GLFW\n";
      return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if(!mWindow){
      std::cerr << "Failed to create GLFW window\n";
      glfwTerminate();
      return false;
    }

    glfwMakeContextCurrent(mWindow);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
      std::cerr << "Failed to initialize GLAD\n";
      return false;
    }
    glViewport(0, 0, width, height);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return true;
  }

  void Window::destroy(){
    if(mWindow){
      glfwDestroyWindow(mWindow);
      mWindow = nullptr;
    }
    glfwTerminate();
  }

  void Window::pollEvents(){
    glfwPollEvents();
  }

  void Window::swapBuffers(){
    glfwSwapBuffers(mWindow);
  }

  bool Window::shouldClose() const{
    return glfwWindowShouldClose(mWindow);
  }

  GLFWwindow* Window::getNativeWindow() const{
    return mWindow;
  }

}