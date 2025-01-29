#pragma once


#include "gameObject.h"
#include <iostream>



class Ball : public gameObject
{
 private:
  float max_angle = 45;
  float pi       = 3.14159;


 public:
  Ball();
  ~Ball();
  bool isColliding(gameObject object, float dt);
  void changeAngle(float y);
};