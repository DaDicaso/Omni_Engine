#pragma once
#include<cmath>


namespace engine{
  using real = float;

  inline real real_sqrt(real x){
    return std::sqrt(x);
  }

  inline real real_pow(real x, real y){
    return std::powf(x, y);
  }
}