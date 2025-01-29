
#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AI.h"
#include "Ball.h"
#include <iostream>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init(bool debug);
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  bool getExitGame();
  void setPlayerNames(std::string p1Name, std::string p2Name);
  void setPlayerTypes(int p1Type, int p2Type);
  int getScoreDifference();
  void setWinCondition(int s);
  

 private:
  
  int win_condition = 5;

  int paddle_bounce_number = 0;

  bool debug    = false;
  bool rectFull = false;
	 sf::RectangleShape* graphRects[217];

  sf::RenderWindow& window;

  sf::Texture background_texture;
  sf::Sprite background_sprite;

  int player1_type = 1; //AI = 0 Player = 1
  int player2_type = 1; //AI = 0 Player = 1


  sf::Font font;
  sf::Text player1_name_text;
  sf::Text player1_score_text;
  int p1_score = 0;

  sf::Text player2_name_text;
  sf::Text player2_score_text;
  int p2_score = 0;

  sf::Text countdown_Text;

  Player players[2] = { Player(0), Player(1)};
  AI player_AI[2]   = { AI(0), AI(1)};

  sf::SoundBuffer paddle_bounce_buffer;
  sf::Sound paddle_bounce_sound;

  sf::SoundBuffer wall_bounce_buffer;
  sf::Sound wall_bounce_sound;  
  
  sf::SoundBuffer ball_out_buffer;
  sf::Sound ball_out_sound;

  sf::Clock ball_release_clock;

  Ball ball;

  bool ball_out = false;

  bool exit_game = false;
};

#endif // PONG_GAME_H
