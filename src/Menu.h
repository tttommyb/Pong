#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"


class Menu
{
 public:
  Menu(sf::RenderWindow& game_window);
  ~Menu();
  bool init();
  void render();
  void loadScoreTable(std::string filePath);
  void saveScoreTable(std::string filePath);
  void displayScoreBoard();
  void addScoreDifferenceToTable(int sd, std::string p1NameCode, std::string p2NameCode);
  void setInMenu(bool iM);
  bool getInMenu();
  void setStartPlay(bool p);
  bool getStartPlay();
  bool getDeubgMode();
  bool getHasQuit();
  void mouseClicked(sf::Event event);
  void textEntered(sf::Event event);
  std::string getPlayer1Name();
  std::string getPlayer2Name();
  int getPlayer2Type();
  int getScore();

 private:

  bool inMenu = true;
  bool startPlay = false;
  bool hasQuit   = false;
  bool debug     = false;

  sf::Font font;

  sf::RenderWindow& window;

  sf::Text title_text;
  
  sf::RectangleShape player1_name_box;
  sf::Text player1_name_text;
  bool in_player1_text_state;


  sf::RectangleShape player2_name_box;
  sf::Text player2_name_text;
  bool in_player2_text_state;

  sf::RectangleShape player2_AI_toggle;
  sf::Text player2_AI_text;

  int score = 5;

  sf::RectangleShape score_condition_box;
  sf::Text score_condition_text;

  sf::RectangleShape score_increase_button;
  sf::Text score_increase_text;

  sf::RectangleShape score_decrease_button;
  sf::Text score_decrease_text;

  sf::RectangleShape debug_line_toggle;
  sf::Text debug_line_text;

  sf::RectangleShape play_button;
  sf::Text play_text;


  sf::RectangleShape quit_button;
  sf::Text quit_text;

  sf::RectangleShape scoreboard;
  sf::Text scoreboard_text;
  int score_difference_table[5];
  std::string name_code_table[10];
  
};