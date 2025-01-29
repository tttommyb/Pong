#pragma once

#include "gameObject.h"
#include <iostream>
#include "SFML/Graphics.hpp"

class AI : public gameObject
{
 private:
  float destination;
  int ai_side; // 0 = left 1 = right


  public:
  AI(int player_num);
  ~AI();
  float getDestination();
  void setDestination(float d);
  void calculateNextPosition(
    double ball_vectX, double ball_vectY, float ball_bounceY, sf::RectangleShape* rectangles[], bool drawDebugLine);
  void resetPosition();
};