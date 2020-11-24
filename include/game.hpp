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
#include "player.hpp"

using namespace std;
using namespace sf;

class game {

    private:
     
    int grid[30][30];       //map with obstacle
    int posX=2,posY=2,destX=25,destY=26; 

    int moves=70;
    int life=3;
    int hints=1;

    Texture background,texPlayer,texPrincess,path,black,emy,imm;
    Sprite bg,princess,paths,obstacle,enemy,immunity;

    Font font;
    Clock clock;
    float dtime=0.0f;

    dijkstra dj;
    Player player;
    


public:


    game();
    ~game();

    void start();
    void Supriya();
    void gameOver();
};