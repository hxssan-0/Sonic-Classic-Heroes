#pragma once
#include <iostream>
#include "Enemies.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

class Crawlers : public Enemies
{
public:
	Crawlers(int hp, float sX, float sY, float eX, float eY, float disX, float disY, float cooldown, bool shoots, string enemyTexPath, float sclX, float sclY, float imgX, float imgY);

	virtual void moveEnemy(float dt, float targetX = 0, float targetY = 0) = 0; //the second argument is default to accomodate those enemies which follow the player

	virtual void update(float dt, float x, RenderWindow& window, float targetX = 0, float targetY = 0, float gravity = 0, float vol = 0, char** lvl = nullptr) = 0;

	virtual Sprite& getNeedleSprite();
};
