#pragma once

struct GLFWwindow;

namespace omni{
  class Window{
    public:

      Window();
      ~Window();

      bool create(int width, int height, const char* title);

      void destroy();

      void pollEvents();

      void swapBuffers();

      bool shouldClose() const;

      GLFWwindow* getNativeWindow() const;

    private:  

      GLFWwindow* mWindow = nullptr;
  };
}