#pragma once

#include "engine/math/vector3.h"

namespace omni{

  class Window;

  class Renderer{
    public:

      Renderer(Window& window);

      void initialize();

      void beginFrame();

      void endFrame();

      void setClearColor(
        float red,
        float green,
        float yellow,
        float aplha
      );

      void drawPoint(const Vector3& position, float size = 12.0f);

    private:
    
      Window& mWindow;
      float mClearColor[4];
  };
}