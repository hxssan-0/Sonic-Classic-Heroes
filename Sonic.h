#pragma once
#include <iostream>
#include "Players.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Sonic : public Players
{
private:
	Texture sonicLeftTex;
	Sprite sonicLeftSprite;
	Texture sonicBallTex;
	Sprite sonicBallSprite;

public:
	Sonic();

	virtual void update(float dt, float x, char** obstacles, RenderWindow&, float vol);

	virtual void moveToTarget(float targetX, float dt, float targetY);

	virtual void jump(float dt);

	virtual void move(float dt, RenderWindow&);

	virtual void activateBoost();
};
