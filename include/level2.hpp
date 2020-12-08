#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include<iostream>

#include<functional>
#include<math.h>
#include<float.h>
#include<vector>
#include<set>
#include<string.h>
#include<string>
#include<sstream>
#include<time.h>

#include "level3.hpp"
#include "bfs.hpp"

using namespace std;
#define N 12

class level2
{
public:
    sf::SoundBuffer bgs, attacked, killed, star, hin, win, gover, ride;
	sf::Sound bgsound, attsound, killsound, hinsound, winsound, goversound, starsound, rsound;

	level2();
	level2(int move, int lfe);
	~level2() {//...
	}


	void start(sf::RenderWindow &window);
	void checkValid(int a, int b);
	void valid(int x, int y);
	void reset(int x, int y);
	void nextlevel(sf::RenderWindow &window);
	void startGame(sf::RenderWindow &window);

	//drawing chessboard size 8*8
	sf::RectangleShape tileMap[N][N];
	int grid[N][N];

private:
	sf::Font fonts;
	sf::Texture texknight, texprincess, texback, rulesTexture,emy;
	sf::Sprite knight, princess, background, rulesSprite,enemy;

	sf::CircleShape sPath;

	float gridSizef = 900 / N;

	int posX = 0, posY = 0, destX, destY;
	float hintX, hintY;
	int moves, score, life;
	bool seeRules = 0;
	bfs bf;

};

