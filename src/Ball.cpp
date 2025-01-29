#include "Ball.h"

Ball::Ball() 
{
  if (!object_texture.loadFromFile("../Data/Images/ball.png"))
  {
    std::cout << "FAILED TO LOAD BALL.PNG" << std::endl;
  }

  object_sprite.setTexture(object_texture);
  object_sprite.setPosition(sf::Vector2f(540, 360));
  object_sprite.setScale(sf::Vector2f(0.25f, 0.25f));

 


  vect_X = -1;
  vect_Y = 1;
  speed = 0;



}

Ball::~Ball() 
{

}

bool Ball::isColliding(gameObject collidingObject, float dt)
{
  float ball_top = object_sprite.getGlobalBounds().top ;
  float ball_bottom = ball_top + object_sprite.getGlobalBounds().height;
  float object_top = collidingObject.getSpritePtr()->getGlobalBounds().top;
  float object_bottom = object_top + collidingObject.getSpritePtr()->getGlobalBounds().height;
  float ball_left = object_sprite.getGlobalBounds().left + vect_X * speed * dt;
  float ball_right  = ball_left + object_sprite.getGlobalBounds().width;
  float object_left = collidingObject.getSpritePtr()->getGlobalBounds().left;
  float object_right =  object_left + collidingObject.getSpritePtr()->getGlobalBounds().width;



  /**
   * Checks if any part of the ball is touching the front face of the paddle
   * if so it will reverse the direction of the ball.
  */
  if (ball_left  < object_right && ball_right > object_left )
  {
    std::cout << "ACTUAL BALL POSITION: " << object_sprite.getPosition().y << std::endl;
    if (!(ball_top < object_bottom != ball_bottom > object_top))
    {
        speed += 0.5f;
        return true;
    }

    /**
     * If the ball hits the top or bottom of the paddle then the balls Y
     * direction is reversed.
     * If the paddle pushes the ball away from the paddle then the balls speed is increased.
    */
    else if (!(ball_top + (vect_Y * speed * dt) > object_bottom + (collidingObject.getVectY() * collidingObject.getSpeed() * dt) != ball_bottom + (vect_Y * speed * dt) < object_top + (collidingObject.getVectY() * collidingObject.getSpeed() * dt)))
    {
      if ((vect_Y < 0 && collidingObject.getVectY() < 0) || (vect_Y > 0 && collidingObject.getVectY() > 0))
      {
        speed += collidingObject.getSpeed()/2;
        
      }
      else
      {
        vect_Y *=  -1;
      }
      object_sprite.move(sf::Vector2f(0, vect_Y * speed * dt));
      
    }
  }
  return false;
}

/**
 * Calculates the angle of the ball based on the distance from the paddle.
 * Uses an exponential function to calculate the angle.
 */
void Ball::changeAngle(float y)
{
  float ballY = object_sprite.getPosition().y + object_sprite.getGlobalBounds().height/2;
  float distance = y - ballY;
  float angle = (2 * max_angle * (1 - (1 / (1 + exp(0.125 * distance))))) - max_angle;
  float distanceDirection = distance / abs(distance);
  setVectors(
    cos(angle * pi / 180) * vect_X / abs(vect_X),
    sin(angle * pi / 180) * vect_Y / abs(vect_Y) * distanceDirection);
}
