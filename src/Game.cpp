
#include "Game.h"



Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

/**
 * Initialases the game
 */

bool Game::init(bool debugMode)
{

  paddle_bounce_number = 0;

  debug = debugMode;


  /**
  *Loads in the sound and image files
  */
  if (!paddle_bounce_buffer.loadFromFile("../Data/Sounds/paddleBounce.wav"))
  {
    std::cout << "FAILED TO LOAD paddle_bounce.WAV" << std::endl;
  }

  paddle_bounce_sound.setBuffer(paddle_bounce_buffer);

  if (!wall_bounce_buffer.loadFromFile("../Data/Sounds/wallBounce.wav"))
  {
    std::cout << "FAILED TO LOAD WALLBOUNCE.WAV" << std::endl;
  }

  wall_bounce_sound.setBuffer(wall_bounce_buffer);

  if (!ball_out_buffer.loadFromFile("../Data/Sounds/ballOut.wav"))
  {
    std::cout << "FAILED TO LOAD BALLOUT.WAV" << std::endl;
  }

  ball_out_sound.setBuffer(ball_out_buffer);

  if (!background_texture.loadFromFile("../Data/Images/pongBackground.png"))
  {
    std::cout << "FAILED TO LOAD PONGBACKGROUND.PNG" << std::endl;
  }

  if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "FAILED TO LOAD PLAY TEXT FONT" << std::endl;
  }  


  background_sprite.setTexture(background_texture);

  /**
   * Initialises the player names and scores
  */

  player1_score_text.setColor(sf::Color::White);
  player1_score_text.setPosition(sf::Vector2f(window.getSize().x/4,  (window.getSize().y/2) - 50));
  player1_score_text.setString("0");
  player1_score_text.setCharacterSize(72);
  player1_score_text.setFont(font);

  player1_name_text.setColor(sf::Color::White);
  player1_name_text.setPosition(sf::Vector2f(window.getSize().x/4,  (window.getSize().y/2) - 110));
  player1_name_text.setString(players[0].getNameCode());
  player1_name_text.setCharacterSize(72);
  player1_name_text.setFont(font);

  player2_score_text.setColor(sf::Color::White);
  player2_score_text.setPosition(sf::Vector2f(3*window.getSize().x/4, (window.getSize().y/2) - 50));
  player2_score_text.setString("0");
  player2_score_text.setCharacterSize(72);
  player2_score_text.setFont(font);

  player2_name_text.setColor(sf::Color::White);
  player2_name_text.setPosition(sf::Vector2f(3*window.getSize().x/4,  (window.getSize().y/2) - 110));
  player2_name_text.setString(players[1].getNameCode());
  player2_name_text.setCharacterSize(72);
  player2_name_text.setFont(font);

  ball_out_sound.setVolume(25);
  wall_bounce_sound.setVolume(25);
  paddle_bounce_sound.setVolume(25);


  /**
   * There are 4 paddles loaded in, 2 player paddles and 2 AI paddles, this
   * decides whether or not the player on the left and right is AI or player
   * controlled. The type of controller that is not used is placed off screen.
  */

  if (player1_type == 0)
  {
    (*players[0].getSpritePtr()).setPosition(sf::Vector2f(-100, -100));
    player_AI[0].resetPosition();
  }
  else if (player1_type == 1)
  {
    (*player_AI[0].getSpritePtr()).setPosition(sf::Vector2f(-100, -100));
    players[0].resetPosition();
  }

  if (player2_type == 0)
  {
    (*players[1].getSpritePtr()).setPosition(sf::Vector2f(-100, -100));
    player_AI[1].resetPosition();
  }
  else if (player2_type == 1)
  {
    (*player_AI[1].getSpritePtr()).setPosition(sf::Vector2f(-100, -100));
    players[1].resetPosition();
  }

  ball.getSpritePtr()->setPosition(sf::Vector2f(540, 360));
  p1_score = 0;
  p2_score = 0;

  ball_out = true;

   return true;
}

void Game::update(float dt)
{

  exit_game = false;


  /**
  * Calculates if the player will move off the screen and prevents this from happening
  */
  float next_player1_position = players[0].getSpritePtr()->getPosition().y +  players[0].getVectY() * players[0].getSpeed() * dt;
  float next_player2_position = players[1].getSpritePtr()->getPosition().y +  players[1].getVectY() * players[1].getSpeed() * dt;


  /**
   * Moves the players and AI paddles
  */

  if (next_player1_position < window.getSize().y - players[0].getSpritePtr()->getGlobalBounds().height && next_player1_position > 0)
  {
     (*players[0].getSpritePtr()).move(sf::Vector2f(0, players[0].getVectY() * players[0].getSpeed() * dt));
  }

  if (next_player2_position < window.getSize().y - players[0].getSpritePtr()->getGlobalBounds().height && next_player2_position > 0)
  {
    (*players[1].getSpritePtr()).move(sf::Vector2f(0, players[1].getVectY() * players[1].getSpeed() * dt));
  }

  if (paddle_bounce_number == 0 && player2_type == 0)
  {
    (player_AI[1].setDestination((*ball.getSpritePtr()).getPosition().y));
  }
  
  (*player_AI[0].getSpritePtr()).move(sf::Vector2f(0, player_AI[0].getVectY() * player_AI[0].getSpeed() * dt));
  (*player_AI[1].getSpritePtr()).move(sf::Vector2f(0, player_AI[1].getVectY() * player_AI[1].getSpeed() * dt));

  /**
  * Countdown timer at the start of the game
  */

  if (ball_release_clock.getElapsedTime() >= sf::seconds(3) && ball_out)
  {
    /**
     * Randomly picks which direction the ball will go
    */
    srand(time(NULL));
    if (rand() % 2 == 0)
    {
      ball.setVectors(ball.getVectX(), -1); 
    }
    else
    {
      ball.setVectors(ball.getVectX(), 1);
    }
    ball.setSpeed(200);
    ball_out = false;
  }

  /**
   * Checks if any of the ai paddles have reached their destination yet, if so then they stop moving.
  */

  if (player1_type == 0)
  {
    if ((player_AI[0].getDestination() < (*player_AI[0].getSpritePtr()).getPosition().y && (player_AI[0].getVectY() > 0)) || (player_AI[0].getDestination() > (*player_AI[0].getSpritePtr()).getPosition().y && (player_AI[0].getVectY() < 0)))
    {
      std::cout << "DESTINATION REACHED";
        player_AI[0].setVectors(0, 0);
    }
  }

  if (player2_type == 0)
  {
    if ((player_AI[1].getDestination() < (*player_AI[1].getSpritePtr()).getPosition().y && (player_AI[1].getVectY() > 0)) || (player_AI[1].getDestination() > (*player_AI[1].getSpritePtr()).getPosition().y && (player_AI[1].getVectY() < 0)))
    {
        player_AI[1].setVectors(0, 0);
    }
  }


  /**
   * Checks if the ball has hit the top or bottom of the screen and changes the
   * direction of the ball
   */

  if ((*ball.getSpritePtr()).getPosition().y + ball.getVectY() * ball.getSpeed() * dt < 0 || (*ball.getSpritePtr()).getPosition().y + (*ball.getSpritePtr()).getGlobalBounds().height +  ball.getVectY() * ball.getSpeed() * dt > window.getSize().y)
  {
    ball.setVectors(ball.getVectX(), -ball.getVectY());
    wall_bounce_sound.stop();
    wall_bounce_sound.play();
  }


  /**
   * Checks if the ball has gone off the screen and resets the ball and
   * increments the respective score
  */
  if ((*ball.getSpritePtr()).getPosition().x <   -(*ball.getSpritePtr()).getGlobalBounds().width || (*ball.getSpritePtr()).getPosition().x > window.getSize().x)
  {
    paddle_bounce_number = 0;

    if ((*ball.getSpritePtr()).getPosition().x > window.getSize().x)
    {
      p1_score++;
      player1_score_text.setString(std::to_string(p1_score));
      if (p1_score >= win_condition)
      {
        std::cout << "WIN";
        exit_game = true;
      }
    }
    else
    {
      p2_score++;
      player2_score_text.setString(std::to_string(p2_score));
      if (p2_score >= win_condition)
      {
        std::cout << "WIN";
        exit_game = true;
      }
    }

     ball_out_sound.stop();
     ball_out_sound.play();
    (*ball.getSpritePtr()).setPosition(sf::Vector2f(524, 344));
     ball.setSpeed(0);
     ball.setVectors(rand() % 1 - 2, rand() % 1 - 2);
     std::cout << ball.getVectY() << std::endl;
     std::cout << ball.getVectX() << std::endl;
     ball_release_clock.restart();
     ball_out = true;



  }

  

  /**
   * Checks for if the ball is coliding with any of the paddles.
   * If the ball is then the direction is reversed and if the opponent is AI
   * then the AI will try to calculate the trajectory of the ball.
  */

  if (ball.isColliding(players[0], dt))
  {
    paddle_bounce_number++;
    players->setSpeed(players->getSpeed() + 0.5f);
    player_AI->setSpeed(players->getSpeed() + 0.5f);


    ball.setVectors(-ball.getVectX(), ball.getVectY());
    ball.changeAngle((*players[0].getSpritePtr()).getPosition().y + (*players[0].getSpritePtr()).getGlobalBounds().height/2 );
    paddle_bounce_sound.stop();
    paddle_bounce_sound.play();
    if (player2_type == 0)
    { 
        player_AI[1].calculateNextPosition( ball.getVectX(), ball.getVectY(), (*ball.getSpritePtr()).getPosition().y, graphRects, debug);
        if (debug)
        {
            rectFull = true;
        }
    }


  }
 
  else if (ball.isColliding(players[1], dt))
  {
    paddle_bounce_number++;
    players->setSpeed(players->getSpeed() + 0.5f);
    player_AI->setSpeed(players->getSpeed() + 0.5f);

    ball.setVectors(-ball.getVectX(), ball.getVectY());
    ball.changeAngle(players[1].getSpritePtr()->getPosition().y + players[1].getSpritePtr()->getGlobalBounds().height/2);
    paddle_bounce_sound.stop();
    paddle_bounce_sound.play();
    if (player1_type == 0)
    {
      player_AI[0].calculateNextPosition( ball.getVectX(),ball.getVectY(), (*ball.getSpritePtr()).getPosition().y, graphRects, debug);
      if (debug)
      {
        rectFull = true;
      }
    }
  }

  else if (ball.isColliding(player_AI[0], dt))
  {
    paddle_bounce_number++;
    players->setSpeed(players->getSpeed() + 0.5f);
    player_AI->setSpeed(players->getSpeed() + 0.5f);

    ball.setVectors(-ball.getVectX(), ball.getVectY());
    ball.changeAngle(player_AI[1].getSpritePtr()->getPosition().y + player_AI[1].getSpritePtr()->getGlobalBounds().height / 2);
    paddle_bounce_sound.stop();
    paddle_bounce_sound.play();
    if (player2_type == 0)
    { 
        player_AI[1].calculateNextPosition( ball.getVectX(), ball.getVectY(), (*ball.getSpritePtr()).getPosition().y, graphRects, debug);
      if (debug)
      {
        rectFull = true;
      }
    }
    
  }
  else if (ball.isColliding(player_AI[1], dt))
  {
    paddle_bounce_number++;
    players->setSpeed(players->getSpeed() + 0.5f);
    player_AI->setSpeed(players->getSpeed() + 0.5f);

    ball.setVectors(-ball.getVectX(), ball.getVectY());
    ball.changeAngle(player_AI[1].getSpritePtr()->getPosition().y + player_AI[1].getSpritePtr()->getGlobalBounds().height/2);
    paddle_bounce_sound.stop();
    paddle_bounce_sound.play();
    if (player1_type == 0)
    { 
        player_AI[0].calculateNextPosition( ball.getVectX(), ball.getVectY(), (*ball.getSpritePtr()).getPosition().y, graphRects, debug);
        if (debug)
        {
            rectFull = true;
        }
    }

  }
  
 
  /**
   * Moves the ball
   */
 
  (*ball.getSpritePtr()).move(sf::Vector2f(ball.getVectX() * ball.getSpeed() * dt, ball.getVectY() * ball.getSpeed() * dt));
  
}

void Game::render()
{
  window.draw(background_sprite);

  /**
   * Draws the ball trajectory debug line
   */
  if (debug)
  {
    int i = 0;
    for (sf::RectangleShape* rect : graphRects)
    {
      if (rectFull)
      {
        window.draw(*rect);
      }
    }
  }

  /**
   * Displays the score information during the countdown
   */

  if (ball_release_clock.getElapsedTime() <= sf::seconds(3))
  {
    window.draw(player1_score_text);
    window.draw(player1_name_text);
    window.draw(player2_score_text);
    window.draw(player2_name_text);
  }
  
  /**
   * Only draws the correct paddle based on the controller type
  */

  switch (player1_type)
  {
    case (0):
      window.draw(*player_AI[0].getSpritePtr());
      break;
    case (1):
      window.draw(*players[0].getSpritePtr());
      break;
  }

  switch (player2_type)
  {
    case (0):
      window.draw(*player_AI[1].getSpritePtr());
      break;
    case (1):
      window.draw(*players[1].getSpritePtr());
      break;
  }

  /**
   * Draws the ball
   */

  window.draw(*(ball.getSpritePtr()));
}


void Game::keyPressed(sf::Event event)
{

    /**
    *Handles the player controller paddle input
    */
  if (player1_type == 1)
  {
    if (event.key.code == sf::Keyboard::W)
    {
      players[0].setVectors(0, players[0].getVectY() - 1);
    }

    else if ( event.key.code == sf::Keyboard::S)
    {
      players[0].setVectors(0, players[0].getVectY() + 1);
    }

  }

  if (player2_type== 1)
  {
    if (event.key.code == sf::Keyboard::Up)
    {
      players[1].setVectors(0, players[1].getVectY() - 1);
    }

    else if (event.key.code == sf::Keyboard::Down)
    {
      players[1].setVectors(0, players[1].getVectY() + 1);
    }
  }

  /**
   * Checls if the player wants to exit the game
  */

  if (event.key.code == sf::Keyboard::Escape)
  {
    exit_game = true;
  }
   
   
}

void Game::keyReleased(sf::Event event)
{
  /**
   * Adjust the player paddle vectors to the direction they want to go
  */
  if (player1_type == 1)
  {
    if (event.key.code == sf::Keyboard::W)
    {
      players[0].setVectors(0, players[0].getVectY() + 1);
    }

    else if (event.key.code == sf::Keyboard::S)
    {
      players[0].setVectors(0, players[0].getVectY() - 1);
    }
  }
 
  if (player2_type == 1)
  { 
    if (event.key.code == sf::Keyboard::Up)
    {
      players[1].setVectors(0, players[1].getVectY() + 1);
    }

    else if (event.key.code == sf::Keyboard::Down)
    {
      players[1].setVectors(0, players[1].getVectY() - 1);
    }
  }
 

}

bool Game::getExitGame() 
{
  return exit_game;
}

void Game::setPlayerNames(std::string p1Name, std::string p2Name) 
{
  /**
  * Sets the names of each player from the name inputted in the menu
   * Set to "AI" if the player is an AI
  */

   std::cout << "PLAYER 1 TYPE: " << player1_type << std::endl;
   std::cout << "PLAYER 2 TYPE: " << player2_type << std::endl;
  if (player1_type == 1)
  {
    players[0].setNameCode(p1Name);
  }
  else
  {
    
    players[0].setNameCode("AI");
  }
  if (player2_type == 1)
  {
    players[1].setNameCode(p2Name);  
  }
  else
  {
    players[1].setNameCode("AI");
  }
}

void Game::setPlayerTypes(int p1Type, int p2Type) 
{
  player1_type = p1Type;
  player2_type = p2Type;
}

int Game::getScoreDifference() 
{

    /**
   * Returns the difference in score between the two players for the scoreboard
    */
  if (p1_score > p2_score)
  {
      return (p1_score - p2_score);
  }
  else
  {
    return (p2_score - p1_score);
  }
}

void Game::setWinCondition(int s)
{
  win_condition = s;
}