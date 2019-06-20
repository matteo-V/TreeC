#include <random>
#include <math.h>
#include "RandomVariable.h"

RandomVariable::RandomVariable(){}
double RandomVariable::uniform(float lower, float upper){
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1.0);
  return(dis(gen));
}
double RandomVariable::exponential(float lam){
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd());
  std::exponential_distribution<> dis(lam);
  return(dis(gen));
}
