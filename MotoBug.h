#pragma once
#include <iostream>
#include "Crawlers.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

class MotoBug : public Crawlers
{
public:
	MotoBug(float eX, float eY);

	virtual void moveEnemy(float dt, float targetX = 0, float targetY = 0);

	virtual void update(float dt, float x, RenderWindow& window, float targetX = 0, float targetY = 0, float gravity = 0, float vol = 0, char** lvl = nullptr);

	virtual Sprite& getNeedleSprite();
};
