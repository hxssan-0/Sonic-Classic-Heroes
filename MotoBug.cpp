#pragma once
#include <iostream>
#include "MotoBug.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

//TODO --- adjust speeds, ranges and coordinates
MotoBug::MotoBug(float eX, float eY) : Crawlers(1, 100.0f, 0, eX, eY, 0, 0, 0.0f, false, "Sprites\\motobug_sprite.png", 2.5f, 2.5f, 39, 28)
{
}

void MotoBug::update(float dt, float x, RenderWindow& window, float targetX, float targetY, float gravity, float vol, char** lvl)
{
	moveEnemy(dt, targetX);
	enemySprite.setPosition(x, enemyY);
}

void MotoBug::moveEnemy(float dt, float targetX, float targetY)
{
	if (abs(targetX - enemyX <= 600.0f)) {
		if (targetX < enemyX) {
			enemyX -= speedX * dt;
		}
		else if (targetX > enemyX) {
			enemyX += speedX * dt;
		}
	}
}

Sprite& MotoBug::getNeedleSprite()
{
	return enemySprite;
}