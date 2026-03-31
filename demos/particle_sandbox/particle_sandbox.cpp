#include<engine/physics/particle.h>
#include<engine/physics/pfgen.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<vector>
#include<random>
#include<memory>

void processInput(GLFWwindow* window);

int main(){
  if(!glfwInit()){
    std::cout << "Failed to initialize the GLFW\n";
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(1920, 1080, "Physics Sandbox", nullptr, nullptr);

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

  glViewport(0, 0, 1920, 1080);

  //float dt = 0.014f; // this is a timestamp since physics engine advances in small time slices.
  #pragma region "projectile motion Particle"
  // std::random_device rd;
  // std::mt19937 gen(rd());
  // std::uniform_real_distribution<> distr(3, 7);
  // std::uniform_real_distribution<> xdistr(-4, 4);

  // std::vector<engine::Particle> particles;
  // particles.resize(1000000);

  // for(int i = 0; i < particles.size(); i++){
  //   particles[i].setPosition(xdistr(gen), distr(gen), 0);
  //   particles[i].setVelocity(distr(gen), distr(gen), 0);
  //   particles[i].setAcceleration(0, -9.8f, 0);
  //   particles[i].setMass(1.0f);
  //   particles[i].setDamping(0.99f);
  // }

  #pragma endregion
  
  #pragma region "Three particle system"
  // engine::Particle p1;
  // engine::Particle p2;
  // engine::Particle p3;

  // p1.setPosition(-3, 0, 0);
  // p2.setPosition(3, 0, 0);
  // p3.setPosition(0, 3, 0);

  // p1.setMass(1);
  // p2.setMass(1);
  // p3.setMass(1);

  // p1.setAcceleration(0,0,0);
  // p2.setAcceleration(0,0,0);
  // p3.setAcceleration(0,0,0);
  // std::vector<engine::Particle> particles(7);

  // for(int i = 0; i < 7; i++)
  // {
  //     particles[i].setPosition(i * 1.5f, 0, 0);
  //     particles[i].setVelocity(0,0,0);
  //     particles[i].setAcceleration(0,-9.8f,0);

  //     particles[i].setMass(1.0f);
  //     particles[i].setDamping(0.99f);
  // }
#pragma endregion



#pragma region "Spring Force Demo with two particle system"
  // engine::Particle p1, p2;
  // engine::ParticleForceRegistry registry;
  // p1.setPosition(0, 5, 0);
  // p1.setMass(1.0f);
  // p1.setDamping(0.99f);
  // p1.setAcceleration(10, 0, 0);

  // p2.setPosition(0, 0, 0);
  // p2.setMass(1.0f);
  // p2.setDamping(0.99f);
  // p2.setAcceleration(-10,0,0);

  // engine::ParticleSpring spring1(&p2, 10.0f, 3.0f);
  // engine::ParticleSpring spring2(&p1, 10.0f, 3.0f);

  // registry.add(&p1, &spring1);
  // registry.add(&p2, &spring2);
  #pragma endregion
  
#pragma region "Rope sim using springs"

  engine::ParticleForceRegistry registry;
  std::vector<engine::Particle> rope;
  int numParticles = 15;
  rope.resize(numParticles);
  float spacing = 0.5f;

  // Instantiate Particles of the ropes
  for(int i =0; i<numParticles; i++){
    rope[i].setPosition(0, 5 - i * spacing, 0);
    rope[i].setVelocity(0, 0, 0);
    rope[i].setMass(1.0f);
    rope[i].setAcceleration(0, 0, 0);
    rope[i].setDamping(0.99f);
  }
  rope[0].setMass(0);
  
  // Instantiate springs between particles
  std::vector<std::unique_ptr<engine::ParticleSpring>> springs;

  springs.reserve((numParticles -1) *2);
  for(int i= 0; i< numParticles -1; i++){
    springs.push_back(std::make_unique<engine::ParticleSpring>(&rope[i+1], 50.0f, spacing));
    registry.add(&rope[i], springs.back().get());

    springs.push_back(std::make_unique<engine::ParticleSpring>(&rope[i], 50.0f, spacing));
    registry.add(&rope[i+1], springs.back().get());
    std::cout << "Connecting " << i << " <-> " << i+1 << std::endl;
  }

  double lastTime = glfwGetTime();
  while(!glfwWindowShouldClose(window)){
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    processInput(window);

    double currentTime = glfwGetTime();
    double dt = currentTime - lastTime;
    lastTime = currentTime;

    #pragma region "Rope Sim using springs"

    registry.updateForces(dt);
    
    for(auto &p : rope){
      p.integrate(dt);
    }
    glPointSize(8);
    glBegin(GL_POINTS);
    for(int i =0; i < numParticles; i++){
      if(i==0) glColor3f(1, 0, 0);
      else glColor3f(0, 1, 0);

      auto pos = rope[i].getPosition();
      glVertex3f(pos.x, pos.y, pos.z);

    }
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    
    for(int i = 0; i < numParticles -1; i++){
      auto p1 = rope[i].getPosition();
      auto p2 = rope[i+1].getPosition();

      glVertex3d(p1.x, p1.y, p1.z);
      glVertex3f(p1.x, p2.y, p2.z);
    }

    glEnd();

    #pragma endregion

    
    #pragma region "Two particle Spring demo"
    //registry.updateForces(dt);
    // glPointSize(10.0f);

    // p1.integrate(dt);
    // p2.integrate(dt);

    // auto pos1 = p1.getPosition();
    // auto pos2 = p2.getPosition();

    // glBegin(GL_POINTS);

    // // p1-> RedColor
    // glColor3f(1.0f, 0.0f, 0.0f);
    // glVertex3f(pos1.x, pos1.y, pos1.z);

    // //p2-> green color
    // glColor3f(0.0f, 1.0f, 0.0f);
    // glVertex3f(pos2.x, pos2.y, pos2.z);

    // glEnd();

    // glColor3f(1.0f, 1.0f, 1.0f);
    // glBegin(GL_LINES);
    // glVertex3f(pos1.x, pos1.y, pos1.z);
    // glVertex3d(pos2.x, pos2.y, pos2.z);
    // glEnd();
    #pragma endregion

    #pragma region "Something related to particle velocity"
    // for(int i = 0; i < particles.size() - 1; i++){
    //   auto pos1 = particles[i].getPosition();
    //   auto pos2 = particles[i+1].getPosition();

    //   engine::Vector3 force = pos1 - pos2;

    //   float length = force.magnitude();

    //   float magnitude = -k * (length - restLength);

    //   force.normalize();
    //   force *= magnitude;

    //   particles[i].addForce(force);
    //   particles[i+1].addForce(-force);
    // }

    // for(int i = 0; i < particles.size(); i++){
    //   particles[i].integrate(dt);
    // }

    // glBegin(GL_LINES);
    // for(int i = 0; i < particles.size() -1 ; i++){
    //   auto pos1 = particles[i].getPosition();
    //   auto pos2 = particles[i+1].getPosition();

    //   glVertex3f(pos1.x, pos1.y, pos1.z);
    //   glVertex3f(pos2.x, pos2.y, pos2.z);
    // }

    // glEnd();
    #pragma endregion

    #pragma region "Springs in a triangle"
    // engine::Vector3 pos1 = p1.getPosition();
    // engine::Vector3 pos2 = p2.getPosition();
    // engine::Vector3 pos3 = p3.getPosition();

    // engine::Vector3 force12 = pos1 - pos2;
    // engine::Vector3 force13 = pos1 - pos3;
    // engine::Vector3 force23 = pos2 - pos3;

    // float length12 = force12.magnitude();
    // float length13 = force13.magnitude();
    // float length23 = force23.magnitude();

    // float restLength = 4.0f;
    // float k = 5.0f;

    // float magnitude12 = -k * (length12 - restLength);
    // float magnitude13 = -k * (length13 - restLength);
    // float magnitude23 = -k * (length23 - restLength);

    // force12.normalize();
    // force13.normalize();
    // force23.normalize();

    // force12 *= magnitude12;
    // force13 *= magnitude13;
    // force23 *= magnitude23;

    // p1.addForce(force13);
    // p3.addForce(-force13);

    // p1.addForce(force12);
    // p2.addForce(-force12);

    // p2.addForce(force23);
    // p3.addForce(-force23);


    // p1.integrate(dt);
    // p2.integrate(dt);
    // p3.integrate(dt);


    // //glPointSize(10);
    // glBegin(GL_LINES);
    // glVertex3f(pos1.x, pos1.y, pos1.z);
    // glVertex3f(pos2.x, pos2.y, pos2.z);
    
    // glVertex3f(pos1.x, pos1.y, pos1.z);
    // glVertex3f(pos3.x, pos3.y, pos3.z);

    // glVertex3f(pos2.x, pos2.y, pos2.z);
    // glVertex3f(pos3.x, pos3.y, pos3.z);
    // glEnd();
    //glBegin(GL_POINTS);
    #pragma endregion

    #pragma region "projectile particle sim"
    /*Summary
      This loop is for multiple particle projectile simulation
    Summary*/
    // glBegin(GL_POINTS);
    // glPointSize(10);
    // for(int i = 0; i < particles.size(); i++){
    //   particles[i].integrate(dt);
    //   auto pos = particles[i].getPosition();
    //   glVertex3f(pos.x, pos.y, pos.z);
    

    //   if(pos.y < -30){
    //     particles[i].setPosition(0, distr(gen), 0);
    //     particles[i].setVelocity(
    //       particles[i].getVelocity().x + distr(gen),
    //       particles[i].getVelocity().y + distr(gen),
    //       0
    //     );
    //   }
    // }
    //glEnd();
    
    #pragma endregion
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
     glfwSetWindowShouldClose(window, true);
  }
}