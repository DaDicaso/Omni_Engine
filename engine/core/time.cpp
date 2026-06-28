#include "engine/core/time.h"

#include "GLFW/glfw3.h"

namespace omni
{
  Time::Time() : mDeltaTime(0.05f), mElapsedTime(0.0f), mLastFrameTime(glfwGetTime()){

  }

  void Time::update(){
    double currentTime = glfwGetTime();

    mDeltaTime = static_cast<float>(currentTime - mLastFrameTime);

    mElapsedTime += mDeltaTime;

    mLastFrameTime = currentTime;
  }

  float Time::getDeltaTime() const{
    return mDeltaTime;
  }

  float Time::getElapsedTime() const{
    return mElapsedTime;
  }
} // namespace omni
