#include "engine/renderer/renderer.h"
#include "engine/core/window.h"
#include "glad/glad.h"


namespace omni{

  Renderer::Renderer(Window& window) : mWindow(window){
    mClearColor[0] = 0.05f;
    mClearColor[1] = 0.05f;
    mClearColor[2] = 0.05f;
    mClearColor[3] = 1.0f;
  }

  void Renderer::initialize(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  void Renderer::beginFrame(){
    glClearColor(
      mClearColor[0],
      mClearColor[1],
      mClearColor[2],
      mClearColor[3]
    );
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
  }

  void Renderer::endFrame(){
    mWindow.swapBuffers();
  }

  void Renderer::setClearColor(float red, float green, float yellow, float alpha){
    mClearColor[0] = red;
    mClearColor[1] = green;
    mClearColor[2] = yellow;
    mClearColor[3] = alpha;
  }

  void Renderer::drawPoint(const Vector3& position, float size){
    glPointSize(size);

    glBegin(GL_POINTS);

    glVertex3f(position.x, position.y, position.z);

    glEnd();
  }
}