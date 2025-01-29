#pragma once
#include "gameObject.h"

class Player : public gameObject
{
 private:
  std::string name_code;
  int player_side; // 0 = left 1 = right

 public:
  Player(int playerNum);
  ~Player();
  std::string getNameCode();
  void setNameCode(std::string name);
  void resetPosition();
 
};