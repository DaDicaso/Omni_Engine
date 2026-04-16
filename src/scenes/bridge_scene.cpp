#include<engine/scenes/bridge_scene.h>
#include<GLFW/glfw3.h>

using namespace engine;

void BridgeScene::init(){
  particles.clear();
  rods.clear();
  cables.clear();
  topParticles.clear();

  int width = 14;
  int numAnchors = 7;

  particles.reserve(width);
  rods.reserve(width);
  cables.reserve(width);
  topParticles.reserve(numAnchors);


  // Create top and fixed particles
  for(int i = 0; i < numAnchors; i++){
    float t = (float)i/(numAnchors-1);
    float x = -width/2 + t * width;

    Particle p;
    p.setPosition(Vector3(x, 3, 0));
    p.setInverseMass(0.0f);

    topParticles.push_back(p);
  }

  // Create horizontal bridge
  for(int i = 0; i < width; i++){
    Particle p;
    p.setPosition(Vector3(i-width/2, 0, 0));
    p.setMass(1.0f);
    p.setAcceleration(Vector3(0, -9.8f, 0));
    p.setDamping(0.99f);

    particles.push_back(p);
  }

  // rod between neighbours.
  for(int i=0; i< width-1; i++){
    ParticleRod rod;
    rod.particle[0] = &particles[i];
    rod.particle[1] = &particles[i+1];

    rod.length = 1.0f;
    rod.maxStress = 0.5f;
    
    rods.push_back(rod);
  }


  // Add suspension cables 
  for(int i = 0; i < numAnchors; i++){

    int start = (i * width) / numAnchors;
    int end = ((i +1) * width) / numAnchors;

    //int spread = 2;

    for(int j = start; j < end; j++){

        ParticleCable cable;

        cable.particle[0] = &topParticles[i];
        cable.particle[1] = &particles[j];

        cable.maxLength = 4.0f;
        cable.restitution = 0.0f;

        cables.push_back(cable);
    }
}

  // fix ends

  particles[0].setInverseMass(0.0f);
  particles[width-1].setInverseMass(0.0f);
}

void BridgeScene::update(float dt){

  particles[particles.size() - 2].addForce(Vector3(1000.0f, 0, 0));
  particles[1].addForce(Vector3(-1000.0f, 0, 0));
  
  //Integrate particles
  for(auto& p : particles){
    p.integrate(dt);
    p.clearAccumulator();
  }

  // Breaking logic
  for(auto& rod : rods){
    if(rod.broken) continue;

    real currentLen = rod.currentLength();
    real stress = fabs(currentLen - rod.length);

    if(stress > rod.maxStress){
      rod.broken = true;
    }
  }
}

void BridgeScene::render(){

  // Top Particles
  glPointSize(8.0f);
  glBegin(GL_POINTS);

  for(auto& p : topParticles){
    auto pos = p.getPosition();
    glColor3f(0, 0, 1);
    glVertex3f(pos.x, pos.y, pos.z);
  }

  glEnd();
  
  // Particles
  glPointSize(6.0f);
  glBegin(GL_POINTS);

  for(auto& p : particles){
    auto pos = p.getPosition();

    if(p.getInverseMass() == 0){
      glColor3f(0, 0, 1); // Fixed = blue
    }
    else{
      glColor3f(1, 1, 1); // others = white
    }
    
    glVertex3f(pos.x, pos.y, pos.z);
  }

  glEnd();

  // Rods
  glBegin(GL_LINES);
  for(auto& rod : rods){
    auto p1 = rod.particle[0]->getPosition();
    auto p2 = rod.particle[1]->getPosition();

    real currentLen = rod.currentLength();
    real stress = fabs(currentLen - rod.length);
    real ratio = stress/rod.maxStress;

    if(rod.broken){
      glColor3f(0.2f, 0.2f, 0.2f); // broken so gray colored
    }
    else if(ratio < 0.5f){
      glColor3f(0, 1, 0); // green
    }
    else if(ratio < 1.0f){
      glColor3f(1, 1, 0); // yellow
    }
    else{
      glColor3f(1, 0, 0);
    }

    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
  }
  glEnd();

  // Cables
  glBegin(GL_LINES);
  
  for(auto& cable : cables){
    auto p1 = cable.particle[0]->getPosition();
    auto p2 = cable.particle[1]->getPosition();

    glColor3f(0.2f, 0.6f, 1.0f);

    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
  }

  glEnd();
}

void BridgeScene::reset(){
  init();
}

void BridgeScene::generateContacts(engine::ParticleContact *contacts, int& count){
  for(auto& rod : rods){
    if(rod.broken) continue;

    unsigned used = rod.addContact(&contacts[count], 1);
    count += used;
  }

  for(auto& cable : cables){
    unsigned used = cable.addContact(&contacts[count], 1);
    count += used;
  }
}