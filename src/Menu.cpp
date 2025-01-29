#include "Menu.h"
#include <iostream>
#include <filesystem>

Menu::Menu(sf::RenderWindow& game_window) : window(game_window) 
{

}

Menu::~Menu() 
{

}

bool Menu::init() 
{

    /**
   * Loads in the font and initialises the UI elements
    */
  if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "FAILED TO LOAD PLAY TEXT FONT" << std::endl;
  }  

  play_button.setOutlineColor(sf::Color::White);
  play_button.setFillColor(sf::Color::Black);
  play_button.setOutlineThickness(1);
  play_button.setSize(sf::Vector2f(100, 25));
  play_button.setPosition(sf::Vector2f(640 - play_button.getGlobalBounds().width/2, 500));

  play_text.setColor(sf::Color::White);
  play_text.setPosition(sf::Vector2f(play_button.getPosition().x + 25, play_button.getPosition().y));
  play_text.setString("PLAY");
  play_text.setCharacterSize(20);
  play_text.setFont(font);

  quit_button.setOutlineColor(sf::Color::White);
  quit_button.setFillColor(sf::Color::Black);
  quit_button.setOutlineThickness(1);
  quit_button.setSize(sf::Vector2f(100, 25));
  quit_button.setPosition(sf::Vector2f(440 - quit_button.getGlobalBounds().width/2, 500));

  quit_text.setColor(sf::Color::White);
  quit_text.setPosition(sf::Vector2f(quit_button.getPosition().x + 25, quit_button.getPosition().y));
  quit_text.setString("QUIT");
  quit_text.setCharacterSize(20);
  quit_text.setFont(font);

  player1_name_box.setOutlineColor(sf::Color::White);
  player1_name_box.setFillColor(sf::Color::Black);
  player1_name_box.setOutlineThickness(1);
  player1_name_box.setSize(sf::Vector2f(120, 43));
  player1_name_box.setPosition(sf::Vector2f(340, 300));
  
  player1_name_text.setColor(sf::Color::White);
  player1_name_text.setPosition(sf::Vector2f(player1_name_box.getPosition().x + 25, player1_name_box.getPosition().y));
  player1_name_text.setString("AAA");
  player1_name_text.setCharacterSize(34);
  player1_name_text.setFont(font);

  player2_name_box.setOutlineColor(sf::Color::White);
  player2_name_box.setFillColor(sf::Color::Black);
  player2_name_box.setOutlineThickness(1);
  player2_name_box.setSize(sf::Vector2f(120, 43));
  player2_name_box.setPosition(sf::Vector2f(619, 300));

  player2_name_text.setColor(sf::Color::White);
  player2_name_text.setPosition(sf::Vector2f(player2_name_box.getPosition().x + 25, player2_name_box.getPosition().y));
  player2_name_text.setString("BBB");
  player2_name_text.setCharacterSize(34);
  player2_name_text.setFont(font);

  player2_AI_toggle.setOutlineColor(sf::Color::White);
  player2_AI_toggle.setFillColor(sf::Color::Black);
  player2_AI_toggle.setOutlineThickness(1);
  player2_AI_toggle.setSize(sf::Vector2f(40, 40));
  player2_AI_toggle.setPosition(sf::Vector2f(699, 360));

  player2_AI_text.setColor(sf::Color::White);
  player2_AI_text.setPosition(sf::Vector2f(player2_AI_toggle.getPosition().x - 50 , player2_AI_toggle.getPosition().y));
  player2_AI_text.setString("AI:");
  player2_AI_text.setCharacterSize(34);
  player2_AI_text.setFont(font);

  score_condition_box.setOutlineColor(sf::Color::White);
  score_condition_box.setFillColor(sf::Color::Black);
  score_condition_box.setOutlineThickness(1);
  score_condition_box.setSize(sf::Vector2f(40, 40));
  score_condition_box.setPosition(sf::Vector2f(520, 420));

  score_condition_text.setColor(sf::Color::White);
  score_condition_text.setPosition(sf::Vector2f(score_condition_box.getPosition().x + 5, score_condition_box.getPosition().y));
  score_condition_text.setString(std::to_string(score));
  score_condition_text.setCharacterSize(34);
  score_condition_text.setFont(font);

  score_increase_button.setOutlineColor(sf::Color::White);
  score_increase_button.setFillColor(sf::Color::Black);
  score_increase_button.setOutlineThickness(1);
  score_increase_button.setSize(sf::Vector2f(40, 40));
  score_increase_button.setPosition(sf::Vector2f(570, 420));

  score_increase_text.setColor(sf::Color::White);
  score_increase_text.setPosition(sf::Vector2f(score_increase_button.getPosition().x + 5, score_increase_button.getPosition().y));
  score_increase_text.setString(">");
  score_increase_text.setCharacterSize(34);
  score_increase_text.setFont(font);

  score_decrease_button.setOutlineColor(sf::Color::White);
  score_decrease_button.setFillColor(sf::Color::Black);
  score_decrease_button.setOutlineThickness(1);
  score_decrease_button.setSize(sf::Vector2f(40, 40));
  score_decrease_button.setPosition(sf::Vector2f(470, 420));


  score_decrease_text.setColor(sf::Color::White);
  score_decrease_text.setPosition(sf::Vector2f(score_decrease_button.getPosition().x + 5, score_decrease_button.getPosition().y));
  score_decrease_text.setString("<");
  score_decrease_text.setCharacterSize(34);
  score_decrease_text.setFont(font);

  title_text.setColor(sf::Color::White);
  title_text.setPosition(sf::Vector2f(window.getSize().x/2 - 175, 100));
  title_text.setString("PONG");
  title_text.setCharacterSize(124);
  title_text.setFont(font);

  scoreboard.setOutlineColor(sf::Color::White);
  scoreboard.setOutlineThickness(2);
  scoreboard.setFillColor(sf::Color::Black);
  scoreboard.setSize(sf::Vector2f(220, 450));
  scoreboard.setPosition(sf::Vector2f(800, 150));

  scoreboard_text.setColor(sf::Color::White);
  scoreboard_text.setPosition(sf::Vector2f(scoreboard.getPosition().x + 5, scoreboard.getPosition().y));
  scoreboard_text.setString("Scoreboard \n");
  scoreboard_text.setCharacterSize(34);
  scoreboard_text.setFont(font);
  scoreboard_text.setLineSpacing(1.5f);

  debug_line_toggle.setOutlineColor(sf::Color::White);
  debug_line_toggle.setFillColor(sf::Color::Black);
  debug_line_toggle.setOutlineThickness(1);
  debug_line_toggle.setSize(sf::Vector2f(40, 40));
  debug_line_toggle.setPosition(sf::Vector2f(150, 20));

  debug_line_text.setColor(sf::Color::White);
  debug_line_text.setPosition(sf::Vector2f(10 , 20));
  debug_line_text.setString("DEBUG: ");
  debug_line_text.setCharacterSize(34);
  debug_line_text.setFont(font);


  /**
  * Loads in the scoretable 
  */

  loadScoreTable("../Data/ScoreTable.txt");

  return true;
}

void Menu::render() 
{
  /**
   * Draws each of the UI elements
  */
  window.draw(title_text);
  window.draw(player1_name_box);
  window.draw(player1_name_text);
  window.draw(player2_name_box);
  window.draw(player2_name_text);
  window.draw(play_button);
  window.draw(play_text);
  window.draw(quit_button);
  window.draw(quit_text);
  window.draw(scoreboard);
  window.draw(scoreboard_text);
  window.draw(player2_AI_toggle);
  window.draw(player2_AI_text);
  window.draw(debug_line_toggle);
  window.draw(debug_line_text);
  window.draw(score_condition_box);
  window.draw(score_condition_text);
  window.draw(score_increase_button);
  window.draw(score_decrease_button);
  window.draw(score_increase_text);
  window.draw(score_decrease_text);
}

/**
 * Loads in the score table stored in a text file
 */
void Menu::loadScoreTable(std::string filePath) 
{
  std::ifstream file;
  file.open(filePath);
  std::string line;
  int index = 0;
  int subtract = 0;
  if (file.is_open())
  {
    while (std::getline(file, line))
    {
      if (index % 3 == 0)
      {
        /**
         * Each score difference is stored in every 3rd line of the text file
        */
        subtract++;
        std::cout << index/3 << std::endl;
        score_difference_table[index / 3] = std::stoi(line);
      }
      else
      {
        /**
         * 2 Names are stored sequentially after each score
         */
        name_code_table[index - subtract] = line;
      }
      std::cout << "Line read: " << line << std::endl;
      index++;
    }
  }
  else
  {
    std::cout << "FAILED TO OPEN TEXT FILE";
  }
  file.close();
  /**
  * Then displays the scoreboard on the menu
  */
  displayScoreBoard();

}


/**
* Stores the values of the name and score difference array in a text file 
* to allow for the scoreboard to be accessed between sessions
 */
void Menu::saveScoreTable(std::string filePath)
{
  std::ofstream file;
  file.open(filePath);

  if (file.is_open())
  {
    for (int i = 0; i <= 4; i++)
    {
      /**
       * Stores the score difference every 3 items, starting from the first
       * index and then between each score difference the names of the players.
      */
      file.clear();
      file << score_difference_table[i] << "\n";
      file << name_code_table[i*2] << "\n";
      file << name_code_table[(i*2) + 1] << "\n";
    }
    file.close();
  }
  else
  {
    std::cout << "FAILED TO OPEN SCORE TABLE WHEN SAVING";
  }
}

/**
 * To display the updated scoreboard on the screen
 */

void Menu::displayScoreBoard() 
{
  scoreboard_text.setString("Scoreboard \n");
  for (int i = 0; i < 5; i++)
  {
    std::string score = std::to_string(score_difference_table[i]);
    if (score_difference_table[i] < 0)
    {
      score = "";
    }
    scoreboard_text.setString(scoreboard_text.getString() + name_code_table[i * 2] + " " + score + " " + name_code_table[(i*2)+1] + "\n");
  }
}

/**
 * After each game the scoreboard is updated, the last entry is removed and the
 * new entry is added to the front
 */

void Menu::addScoreDifferenceToTable(int sd, std::string p1NameCode, std::string p2NameCode) 
{
  for (int i = 4; i > 0; i--)
  {
    score_difference_table[i]   = score_difference_table[i - 1];
    name_code_table[i * 2] = name_code_table[(i * 2) - 2];
    name_code_table[(i * 2) + 1] = name_code_table[(i * 2) - 1];
  }
  score_difference_table[0] = sd;
  name_code_table[0]       = p1NameCode;
  name_code_table[1]       = p2NameCode;
  displayScoreBoard();
  saveScoreTable("../Data/ScoreTable.txt");
}

bool Menu::getInMenu() 
{
  return inMenu;
}

void Menu::setInMenu(bool iM) 
{
    inMenu = iM;
}

bool Menu::getStartPlay()
{
  return startPlay;
}

void Menu::setStartPlay(bool p)
{
  startPlay = p;
}

bool Menu::getHasQuit() 
{
  return hasQuit;
}


/**
 * Checks if the debug mode is enabled
 */
bool Menu::getDeubgMode()
{
  if (debug_line_toggle.getFillColor() == sf::Color::White)
  {
    return true;
  }
  else
  {
    return false;
  }
}   


/**
 * Handles the mouse click events on the menu
 */
void Menu::mouseClicked(sf::Event event) 
{
  in_player1_text_state              = false;
  in_player2_text_state              = false;
  sf::RectangleShape rectangles[] = {quit_button, play_button, player1_name_box, player2_name_box};
  if (event.mouseButton.button == sf::Mouse::Button::Left)
  {
    if (
      event.mouseButton.x > play_button.getPosition().x &&
      event.mouseButton.x < play_button.getPosition().x + play_button.getGlobalBounds().width &&
      event.mouseButton.y > play_button.getPosition().y &&
      event.mouseButton.y < play_button.getPosition().y + play_button.getGlobalBounds().height)
    {
      inMenu = false;
      startPlay = true;
      return;
    }

    else if (  
      event.mouseButton.x > quit_button.getPosition().x &&
      event.mouseButton.x < quit_button.getPosition().x + quit_button.getGlobalBounds().width &&
      event.mouseButton.y > quit_button.getPosition().y &&
      event.mouseButton.y < quit_button.getPosition().y + quit_button.getGlobalBounds().height)
    {
      hasQuit = true;
      return;   
    }

    else if (  
      event.mouseButton.x > player1_name_box.getPosition().x &&
      event.mouseButton.x < player1_name_box.getPosition().x + player1_name_box.getGlobalBounds().width &&
      event.mouseButton.y > player1_name_box.getPosition().y &&
      event.mouseButton.y < player1_name_box.getPosition().y + player1_name_box.getGlobalBounds().height)
    {
      in_player1_text_state = true;
      player1_name_text.setString("");
      return;
    }

      else if (  
      event.mouseButton.x > player2_name_box.getPosition().x &&
      event.mouseButton.x < player2_name_box.getPosition().x + player2_name_box.getGlobalBounds().width &&
      event.mouseButton.y > player2_name_box.getPosition().y &&
      event.mouseButton.y < player2_name_box.getPosition().y + player2_name_box.getGlobalBounds().height)
        {
        if (player2_AI_toggle.getFillColor() == sf::Color::Black)
        {
          in_player2_text_state = true;

          player2_name_text.setString("");
          return;
        }   
            
        }


      else if (  
      event.mouseButton.x > player2_AI_toggle.getPosition().x &&
      event.mouseButton.x < player2_AI_toggle.getPosition().x + player2_AI_toggle.getGlobalBounds().width &&
      event.mouseButton.y > player2_AI_toggle.getPosition().y &&
      event.mouseButton.y < player2_AI_toggle.getPosition().y + player2_AI_toggle.getGlobalBounds().height)
        {
        if (player2_AI_toggle.getFillColor() == sf::Color::Black)
        {
          player2_name_text.setString("AI");
          player2_AI_toggle.setFillColor(sf::Color::White);
        }
        else if (player2_AI_toggle.getFillColor() == sf::Color::White)
        {
          player2_AI_toggle.setFillColor(sf::Color::Black);
        }
        return;
        }

    else if (
          event.mouseButton.x > debug_line_toggle.getPosition().x &&
          event.mouseButton.x < debug_line_toggle.getPosition().x +
                                  debug_line_toggle.getGlobalBounds().width &&
          event.mouseButton.y > debug_line_toggle.getPosition().y &&
          event.mouseButton.y < debug_line_toggle.getPosition().y +
                                  debug_line_toggle.getGlobalBounds().height)
        {
          if (debug_line_toggle.getFillColor() == sf::Color::Black)
          {
            debug_line_toggle.setFillColor(sf::Color::White);
          }
          else if (debug_line_toggle.getFillColor() == sf::Color::White)
          {
            debug_line_toggle.setFillColor(sf::Color::Black);
          }
          return;
        }

     else if (
          event.mouseButton.x > score_increase_button.getPosition().x &&
          event.mouseButton.x < score_increase_button.getPosition().x +
                                  score_increase_button.getGlobalBounds().width &&
          event.mouseButton.y > score_increase_button.getPosition().y &&
          event.mouseButton.y < score_increase_button.getPosition().y +
                                  score_increase_button.getGlobalBounds().height)
        {
            score++;
          score_condition_text.setString(std::to_string(score));
        }

       else if (
          event.mouseButton.x > score_decrease_button.getPosition().x &&
          event.mouseButton.x < score_decrease_button.getPosition().x +
                                  score_decrease_button.getGlobalBounds().width &&
          event.mouseButton.y > score_decrease_button.getPosition().y &&
          event.mouseButton.y < score_decrease_button.getPosition().y +
                                  score_decrease_button.getGlobalBounds().height)
        {
         if (score > 1)
         {
           score--;
           score_condition_text.setString(std::to_string(score));
         }  
        }
   
   
  }
}

/**
 * Handles the text input events for the name input boxes
 */
void Menu::textEntered(sf::Event event)
{
  if (event.text.unicode < 128)
  { 
    std::cout << (event.text.unicode);
  }
  if (in_player1_text_state)
  {
    // 8 is the backspace key
    if (event.text.unicode == 8)
    {
      if (!player1_name_text.getString().isEmpty())
      {
        int size = player1_name_text.getString().getSize();
        sf::String tempString = player1_name_text.getString();
        tempString.erase(size - 1);
        player1_name_text.setString(tempString);
        
      }
    }
    // Caps the string size to 3 characters
    else if (player1_name_text.getString().getSize() < 3)
    {
        player1_name_text.setString(player1_name_text.getString() + event.text.unicode);
    }
  }
  else if (in_player2_text_state)
  {
    if (event.text.unicode == 8)
    {
      if (!player2_name_text.getString().isEmpty())
      {
        int size = player2_name_text.getString().getSize();
        sf::String tempString = player2_name_text.getString();
        tempString.erase(size - 1);
        player2_name_text.setString(tempString);
        
      }
    }
    else if (player2_name_text.getString().getSize() < 3)
    {
        player2_name_text.setString(player2_name_text.getString() + event.text.unicode);
    }
  }
}

std::string Menu::getPlayer1Name() 
{
  return (player1_name_text.getString());
}

std::string Menu::getPlayer2Name()
{
  return (player2_name_text.getString());
}

int Menu::getPlayer2Type()
{
  if (player2_AI_toggle.getFillColor() == sf::Color::White)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int Menu::getScore() 
{
  return score;
}