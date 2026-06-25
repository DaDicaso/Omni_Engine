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

  inline real real_abs(real x){
    return std::fabsf(x);
  }

  inline real real_sin(real x){
    return std::sinf(x);
  }

  inline real real_cos(real x){
    return std::cosf(x);
  }

  inline real real_exp(real x){
    return std::expf(x);
  }
}