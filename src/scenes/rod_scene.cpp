#include<engine/scenes/rod_scene.h>
#include<GLFW/glfw3.h>
#include<iostream>

using namespace engine;

void RodScene::init(){
  particles.clear();
  rods.clear();

  int N = 10;

  for(int i =0; i < N; i++){
    Particle p;
    p.setPosition(Vector3(-i, 5, 0));
    p.setAcceleration(Vector3(0, -9.8f, 0));
    p.setDamping(0.99f);
    p.setMass(1.0f);
    particles.push_back(p);
  }

  for(int i =0; i < N-1; i++){
    ParticleRod rod;
    rod.particle[0] = &particles[i];
    rod.particle[1] = &particles[i+1];
    rod.length = 1.0f;

    rod.maxStress = 0.5f;
    rod.broken = false;

    rods.push_back(rod);
  }

  particles[0].setInverseMass(0.0f);
  particles[N-1].setInverseMass(0.0f);
}

void RodScene::update(float dt){

  // Adds a constant force to the middle particle
  // particles[particles.size()/2].addForce(Vector3(0, -50, 0));

  // Integrate
  for(auto& p : particles){
    p.integrate(dt);
    p.clearAccumulator();
  }

  for(auto& rod : rods){
    
    if(rod.broken) continue;

    real currentLen = rod.currentLength();
    real stress = fabs(currentLen - rod.length);

    if(stress > rod.maxStress) rod.broken = true;
  }
}

void RodScene::render(){

  //std::cout << "Now Rendering\n";
  glPointSize(6.0f);
  glBegin(GL_POINTS);

  for(auto& particle : particles){
    auto pos = particle.getPosition();

    if(particle.getInverseMass() == 0){
      glColor3f(1, 0, 0);
    }else{
      glColor3f(1, 1, 1);
    }
    glVertex3f(pos.x, pos.y, pos.z);
    
  }

  glEnd();


  glBegin(GL_LINES);

  for(auto& rod : rods){

    auto p1 = rod.particle[0]->getPosition();
    auto p2 = rod.particle[1]->getPosition();

    real currentLen = rod.currentLength();
    real stress = fabs(currentLen - rod.length);
    real ratio = stress/rod.maxStress;

    if(rod.broken){
      glColor3f(0.2f, 0.2f, 0.2f); // Broken
    }
    else if(ratio < 0.5f){
      glColor3f(0, 1, 0); // green
    }
    else if(ratio < 1.0){
      glColor3f(1, 1, 0); // yellow
    }
    else {
      glColor3f(1, 0, 0); // red
    }
    

    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
  }

  glEnd();
}

void RodScene::reset(){
  init();
}

void RodScene::generateContacts(ParticleContact *contacts, int& count){
  
  for(auto& rod : rods){

    if(rod.broken) continue;

      unsigned used = rod.addContact(&contacts[count], 1);
      count += used;
  }
}