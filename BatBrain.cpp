#pragma once
#include <iostream>
#include "BatBrain.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

//TODO --- adjust speeds, ranges and coordinates
BatBrain::BatBrain(float eX, float eY) : Flyers(1, 150.0f, 100.0f, eX, eY, 0, 0, 0.0f, false, "Sprites\\batbrain_sprite.png", -2.5f, 2.5f, 32, 30)
{
}

void BatBrain::update(float dt, float x, RenderWindow& window, float targetX, float targetY, float gravity, float vol, char** lvl)
{
	moveEnemy(dt, targetX, targetY);
	enemySprite.setPosition(x, enemyY);
}

void BatBrain::moveEnemy(float dt, float targetX, float targetY)
{
	if (abs(targetX - enemyX <= 600.0f)) {
		if (targetX < enemyX) {
			enemyX -= speedX * dt;
		}
		else if (targetX > enemyX) {
			enemyX += speedX * dt;
		}

		if (enemyY < targetY)
			enemyY += speedY * dt;
		else if (enemyY > targetY)
			enemyY -= speedY * dt;
	}
}

Sprite& BatBrain::getNeedleSprite()
{
	return enemySprite;
}