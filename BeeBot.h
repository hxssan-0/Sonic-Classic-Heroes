#pragma once
#include <iostream>
#include "Flyers.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

class BeeBot : public Flyers
{
private:
	bool movingLeft;
	bool movingDown;
	Clock projectileClk;
	SoundBuffer shootBuffer;
	Sound shootSound;
public:
	BeeBot(float eX, float eY);

	virtual void moveEnemy(float dt, float targetX = 0, float targetY = 0);

	virtual void update(float dt, float x, RenderWindow& window, float targetX = 0, float targetY = 0, float gravity = 0, float vol = 0, char** lvl = nullptr);

	void shootProjectile(float dt, float x, float targetX, float vol); //give this only to those enemies which shoot

	virtual Sprite& getNeedleSprite();
};