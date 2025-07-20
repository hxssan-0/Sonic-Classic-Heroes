#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Levels.h"
using namespace std;
using namespace sf;

class Level1 : public Levels
{
public:
	Level1(int&, int highscore);

	~Level1();

	virtual void createBackground();

	virtual void createObstacles();

	virtual void createEnemies();

	virtual void createCollectibles();

	virtual void drawCollectibles(RenderWindow&);

	virtual void drawObstacles(RenderWindow&);

	virtual bool isLevelWon();

	virtual bool isLevelLost();

	virtual void followActivePlayer(int i, RenderWindow& window);

	virtual void runLevel(RenderWindow&);

	virtual void flyWithTails(int i, RenderWindow& window);

	void switchActivePlayer();

};