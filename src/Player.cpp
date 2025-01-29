#include "Player.h"
#include <iostream>



Player::Player(int player_num) : player_side(player_num)
{
  /**
  * Loads in paddle images based on the side of the screen the paddle is on
  */
  switch (player_num)
  {
    case (0):
      if (!object_texture.loadFromFile("../Data/Images/paddleBlue.png"))
      {
        std::cout << "FAILED TO LOAD BLUE PLAYER PNG" << std::endl;
      }
      break;
    default:
      if (!object_texture.loadFromFile("../Data/Images/paddleRed.png"))
      {
        std::cout << "FAILED TO LOAD RED PLAYER PNG" << std::endl;
      }
      break;
  }

  object_sprite.setTexture(object_texture);
  object_sprite.setPosition(sf::Vector2f(100 + (880 * player_num), 50));
  object_sprite.rotate(90);

  speed = 200;

  controller_type = 1;
}

Player::~Player() 
{

}

std::string Player::getNameCode() 
{
  return name_code;
}

void Player::setNameCode(std::string name)
{
  name_code = name;
}

void Player::resetPosition() 
{
  object_sprite.setPosition(sf::Vector2f(100 + (880 * player_side), 50));
}