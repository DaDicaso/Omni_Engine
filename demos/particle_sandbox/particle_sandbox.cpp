#include<GLFW/glfw3.h>
#include<iostream>

#include "engine/scenes/rod_scene.h"
#include "engine/scenes/bridge_scene.h"
#include "engine/scenes/physics_lab_scene.h"
#include "engine/physics/pcontacts.h"

using namespace omni;

static const unsigned MAX_CONTACTS = 100;

omni::ParticleContact contacts[MAX_CONTACTS];
omni::ParticleContactResolver resolver(100);

void processInput(GLFWwindow *window);
Vector3 getMouseWorld(GLFWwindow* window);

float getDeltaTime(){
  static float last = glfwGetTime();
  float current = glfwGetTime();
  float dt = current - last;

  if (dt > 0.02f) dt = 0.02f;   // ~50 FPS cap
  if (dt < 0.001f) dt = 0.001f; // avoid tiny steps
  last = current;
  return dt;
}

int main(){
  if(!glfwInit()){
    std::cout << "GLFW init failed\n";
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(1920, 1080, "Particle Sandbox", NULL, NULL);
  glfwMakeContextCurrent(window);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-17.77, 17.77, -10, 10, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0, 0, 0, 1);

  PhysicsLabScene labScene;
  BridgeScene bridgeScene;
  

  Scenes *currentScene = &bridgeScene;


  //currentScene->init();
  /////////////////////////////
  /** <LOOP>
  /* Here is the main loop
  /* </LOOP>*/
  ////////////////////////////

  while(!glfwWindowShouldClose(window)){
    
    float dt = getDeltaTime();
    
    processInput(window);

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS){
      Vector3 mousePos = getMouseWorld(window);

      Particle* p = bridgeScene.getClosestParticle(mousePos);

      if(p && p->hasFiniteMass()){
        Vector3 dir = mousePos - p->getPosition();
        p->addForce(dir * 100.0f);
      }
    }

    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
      currentScene = &labScene;
      currentScene->init();
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
      currentScene = &bridgeScene;
      currentScene->init();
    }

    
    //rodScene.particles[rodScene.particles.size()/2].addForce(Vector3(0, -50, 0));
    
    static float accumulator = 0.0f;
    float fixedDt = 0.01f; // 100 Hz simulation
    
    accumulator += dt;
    
    
    while(accumulator >= fixedDt){
      
      // Update
      currentScene->update(fixedDt);
      
      // Contacts
      int contactCount = 0;
      currentScene->generateContacts(contacts, contactCount);
      resolver.resolveContacts(contacts, contactCount, fixedDt);
      
      accumulator -= fixedDt;
    }
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    // Render
    currentScene->render();

    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }
}

Vector3 getMouseWorld(GLFWwindow* window){

  double mx, my;
  glfwGetCursorPos(window,  &mx, &my);

  int width, height;
  glfwGetWindowSize(window, &width, &height);

  // Normalize the mouse input in [-1, 1]
  float x = (mx / width) * 2.0f - 1.0f;
  float y = 1.0f - (my / height) * 2.0f;

  // Map to ortho
  float worldX = x * 17.77f;
  float worldY = y * 10.0f;

  return Vector3(worldX, worldY, 0);
}