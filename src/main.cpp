#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

int main()
{
  std::cout << "You should see a window that opens as well as this writing to console..."
            << std::endl;

  // create window and set up
  sf::RenderWindow window(sf::VideoMode(1080, 720), "Pong");
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);
  // initialise an instance of the game class
  
  Game game(window);
  Menu menu(window);


  if (!menu.init())
  {
    return 0;
  }


  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;

    // calculate delta time
    sf::Time time = clock.restart();
    float dt      = time.asSeconds();

    //'process inputs' element of the game loop
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      if (event.type == sf::Event::MouseButtonPressed)
      {
        if (menu.getInMenu() == true)
        {
          menu.mouseClicked(event);
        }
      }


      if (event.type == sf::Event::KeyPressed)
      {
        if (menu.getInMenu() == false)
        {
            game.keyPressed(event);
        }
      }

       if (event.type == sf::Event::TextEntered)
       {
         if (menu.getInMenu() == true)
         {
            menu.textEntered(event);
         }
       }

      else if (event.type == sf::Event::KeyReleased)
      {
        if (menu.getInMenu() == false)
        {
          game.keyReleased(event);
        }
      }
    }

    window.clear(sf::Color::Black);
     
     if (menu.getStartPlay() == true)
     {
       game.setPlayerTypes(1, menu.getPlayer2Type());
       game.setPlayerNames(menu.getPlayer1Name(), menu.getPlayer2Name());
       game.setWinCondition(menu.getScore());
       if (!game.init(menu.getDeubgMode()))
       {
         return 0;
       }
       menu.setStartPlay(false);
     }
     if (menu.getInMenu() == false)
     {
       if (game.getExitGame())
       {
         menu.setInMenu(true);
         menu.addScoreDifferenceToTable(game.getScoreDifference(), menu.getPlayer1Name(), menu.getPlayer2Name());
       }
       //'update' element of the game loop
       game.update(dt);

       //'render' element of the game loop
       game.render();


     }
     else
     {
       menu.render();

       if (menu.getHasQuit())
       {
         menu.saveScoreTable("../Data/ScoreTable.txt");
         return 0;
       }
     }
 
    window.display();
  }
  menu.saveScoreTable("../Data/ScoreTable.txt");
  return 0;
}
