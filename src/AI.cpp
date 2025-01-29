#include "AI.h"
#include <cmath>

AI::AI(int playerNum) :  ai_side(playerNum)
{
  srand(time(NULL));

   /**
   * Loads in paddle images based on the side of the screen the paddle is on
   */
  switch (playerNum)
  {
    case (0):
      if (!object_texture.loadFromFile("../Data/Images/paddleBlue.png"))
      {
        std::cout << "FAILED TO LOAD BLUE PLAYER PNG";
      }
      break;
    default:
      if (!object_texture.loadFromFile("../Data/Images/paddleRed.png"))
      {
        std::cout << "FAILED TO LOAD RED PLAYER PNG";
      }
      break;

     
  }

  object_sprite.setTexture(object_texture);
  object_sprite.setPosition(sf::Vector2f(100 + (880 * playerNum), 200));
  object_sprite.rotate(90);
  speed = 200;

  controller_type = 0;

  std::cout << "CREATED AI" << std::endl;

   
}

AI::~AI() 
{

}


float AI::getDestination()
{
  return destination;
}

void AI::setDestination(float d)
{
  /**
   * Ensures the destination is within the bounds of the screen
  */

  destination = d;
  std::cout << "REAL DESTINATION: " << destination <<std::endl;
  if (destination > (720 - 104))
  {
    destination = (720 - 104);
  }
  else if (destination < 0 )
  {
    destination = 0;
  }
  else
  {
    destination = destination - (object_sprite.getGlobalBounds().height/2) + 20;
  }

  if (destination > object_sprite.getPosition().y)
  {
    setVectors(0, 1);
  }
  else if (destination < object_sprite.getPosition().y)
  {
    setVectors(0, -1);
  }
  else
  {
    setVectors(0, 0);
  }
}

/**
* Calculates the position that the paddle should move to hit the ball
 * Does not work as intended as it cannot handle the instance when the ball does not bounce off the walls.
 */

void AI::calculateNextPosition(double ball_vectX, double ball_vectY, float ball_bounceY, sf::RectangleShape* rectangles[], bool drawDebugLine)
{
  /**
   * Defines the variables used in the calculation
  */
    float screenHeight  = 688;
    //Slope is the gradient of the ball and is inversely propttional to the spacing between bounces
    double slope       = -688/(ball_vectY / ball_vectX); 
    double c = ball_bounceY;
    double x            = object_sprite.getPosition().x - 100;
    double norm_x       = (x / slope) - (c/screenHeight);
    double floor_value;
    /**
    * Normalizes the x value to the screen space
    * Ensures that the norm_x is rounded towards 0
    */
    if (norm_x >= 0 || (ball_vectY > 0))
    {
    floor_value = std::floor(norm_x);
    }
    else if (norm_x < 0)
    {
    floor_value = std::ceil(norm_x);
    }
    double mod_value = std::fmod(floor_value, 2);

    /**
    * An equation that calculataes where the ball will be at a given x value
    * Based on this graph https://www.desmos.com/calculator/itbhielpgd    
    */ 
    setDestination(std::abs(screenHeight * (((norm_x - floor_value) * (-1 + (2 * mod_value))) - mod_value)));

    std::cout << "NormX value - " << norm_x << std::endl;
    std::cout << "Floor value - " << floor_value << std::endl;
    std::cout << "Mod value - " << mod_value << std::endl;

      
    std::cout << "BALL Y VECTOR: " << ball_vectY << std::endl;
    std::cout << "BALL X VECTOR: " << ball_vectX << std::endl;

    std::cout << std::endl << std::endl << "DESTINATION: " << destination << std::endl;
    std::cout << "PADDLE POSITION(X): " << x << std::endl;
    std::cout << "SLOPE: " << slope << std::endl;
    std::cout << "BALL BOUNCE (Y): " << c << std::endl;
    std::cout << "D: " << norm_x << std::endl;


    /**
    * Draws the predicted trajectory of the ball
     * Loops through the screen width and calculates the y value of the ball at
     * that point and sets the square position to that point for drawing.
    */
    if (drawDebugLine)
    {
    for (int i = 0; i <= 1080; i += 5)
    {
          
        slope  = -688 / (ball_vectY / ball_vectX);
        c      = ball_bounceY;
        x      = i - 100;
        norm_x = (x / slope) - (c / screenHeight);
        if (norm_x >= 0 || (ball_vectY > 0))
        {
        floor_value = std::floor(norm_x);
        }
        else if (norm_x < 0)
        {
        floor_value = std::ceil(norm_x);
        }
        mod_value = std::fmod(floor_value, 2);

        rectangles[i / 5] = new sf::RectangleShape();
        rectangles[i / 5]->setSize(sf::Vector2f(5.f, 5.f));
        if (std::abs(screenHeight *(((norm_x - floor_value) * (-1 + (2 * mod_value))) - mod_value)) > 688)
        {
        rectangles[i / 5]->setPosition(sf::Vector2f(50, 50));
        }
        rectangles[i / 5]->setPosition(sf::Vector2f(i, std::abs(screenHeight *(((norm_x - floor_value) * (-1 + (2 * mod_value))) - mod_value))));
        rectangles[i / 5]->setFillColor(sf::Color::White);
    }

       
    }

  return;
}

void AI::resetPosition()
{
  object_sprite.setPosition(sf::Vector2f(100 + (880 * ai_side), 50));
}


