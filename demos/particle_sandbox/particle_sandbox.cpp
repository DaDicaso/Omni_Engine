#include<engine/physics/particle.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

int main(){
  if(!glfwInit()){
    std::cout << "Failed to initialize the GLFW\n";
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(800, 600, "Physics Sandbox", nullptr, nullptr);

  if(!window){
    std::cout << "Failed to create the window" << std::endl;
    return -1; 
  }

  
  glfwMakeContextCurrent(window);
  
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10, -1, 1);

  glViewport(0, 0, 800, 600);

  float dt = 0.014f; // this is a timestamp since physics engine advances in small time slices.

  engine::Particle particle;

  particle.setPosition(0, 5, 0);
  particle.setVelocity(2, 0, 0);
  particle.setAcceleration(0, -9.8f, 0);
  particle.setMass(1.0f);
  particle.setDamping(0.99f);


  while(!glfwWindowShouldClose(window)){
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    particle.integrate(dt);

    auto pos = particle.getPosition();

    glPointSize(10);

    glBegin(GL_POINTS);
    glVertex3f(pos.x, pos.y, pos.z);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}