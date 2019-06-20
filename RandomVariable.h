#include <random>
#include <math.h>
#ifndef RANDOMVARIABLE_H
#define RANDOMVARIABLE_H



class RandomVariable{
protected:
  //Standard mersenne_twister_engine seeded with rd()
public:
  RandomVariable();
  double uniform(float lower, float upper);
  double exponential(float lam); 
};

#endif
