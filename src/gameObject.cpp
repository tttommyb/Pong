#include "gameObject.h"
#include <cmath>
#include "iostream"

gameObject::gameObject()
{
	
}

gameObject::~gameObject() 
{

}

double gameObject::getSpeed() 
{
  return speed;
}

void gameObject::setSpeed(double s) 
{
  speed = s;
}

float gameObject::getVectX() 
{
  return vect_X;
}

float gameObject::getVectY() 
{
  return vect_Y;
}

void gameObject::setVectors(float x, float y) 
{
  if (x == 0 && y == 0)
  {
    vect_X = 0;
    vect_Y = 0;
    return;
  }
  // normalizes the vector
  float magnitude = hypot(x, y);
  vect_X = x / magnitude;
  vect_Y = y / magnitude;
}

sf::Sprite* gameObject::getSpritePtr() 
{
  return &object_sprite;
}

int gameObject::getControllerType()
{
  return controller_type;
}