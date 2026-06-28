#pragma once

namespace omni
{
  class Time{

    public:
    
      Time();
      
      void update();

      float getDeltaTime() const;

      float getElapsedTime() const;

    private:
    
      float mDeltaTime;
      float mElapsedTime;

      double mLastFrameTime;
  };
} // namespace omni
