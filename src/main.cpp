
#include<iostream>
#include "MainMenu.hpp"
#include "level2.hpp"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1002, 900), "Level 1");
    level2 game(30,5);
    game.start(window);

    // MainMenu menu;
    // menu.Start();

    // GameLevel3 game(30);
    // game.start();

    // intPage page;
    // page.Start();

    
}

