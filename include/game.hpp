#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<functional>        
#include<math.h>        
#include<float.h>
#include<vector>
#include<set>
#include<string.h>
#include<string>
#include<sstream>

#include "dijkstra.hpp"

using namespace std;
using namespace sf;

class game {

    private:
     int filled[num][num];       //cells except for the walking path
    int grid[30][30];       //map with obstacle
    int posX=2,posY=2,destX=25,destY=26; 

    int moves=60;

    Texture background,texPlayer,texPrincess,path,black;
    Sprite bg,player,princess,paths,obstacle;

    Font font;

    dijkstra dj;
    


public:

    game();
    ~game();

    void start();
    void Supriya();
    void gameOver();
};