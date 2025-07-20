#pragma once
#include <iostream>
#include "Players.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Tails : public Players
{
private:
	int flyTime;
public:
	Tails();

	virtual void update(float dt, float x, char** obstacles, RenderWindow& window, float vol);

	virtual void moveToTarget(float targetX, float dt, float targetY);

	virtual void jump(float dt);

	void fly(float dt);

	virtual void move(float dt, RenderWindow& window);

	virtual void activateBoost();
};
