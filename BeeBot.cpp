#pragma once
#include <iostream>
#include "BeeBot.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

//TODO --- adjust speeds, ranges and coordinates
BeeBot::BeeBot(float eX, float eY) : Flyers(1, 150.0f, 100.0f, eX, eY, 200.0f, 200.0f, 5.0f, true, "Sprites\\beebot_sprite.png", 2.5f, 2.5f, 45, 19)
{
	movingLeft = false;
	movingDown = true;
	projectileTex.loadFromFile("Sprites\\projectile_sprite.png");
	projectileSprite.setTexture(projectileTex);
	projectileSprite.setScale(3.0, 3.0);
	projectileSprite.setPosition(enemyX, enemyY);
	projectileClk.restart();
	shootBuffer.loadFromFile("Sprites\\Sounds\\Global\\Explosion.wav");
	shootSound.setBuffer(shootBuffer);
}

void BeeBot::update(float dt, float x, RenderWindow& window, float targetX, float targetY, float gravity, float vol, char** lvl)
{
	moveEnemy(dt);
	shootProjectile(dt, x, targetX, vol);
	enemySprite.setPosition(x, enemyY);
}

void BeeBot::moveEnemy(float dt, float targetX, float targetY)
{
	//zig zag pattern
	if (movingLeft) {
		enemyX -= speedX * dt;
	}
	else {
		enemyX += speedX * dt;
	}

	if (movingDown) {
		enemyY += speedY * dt;
	}
	else {
		enemyY -= speedY * dt;
	}

	dX += speedX * dt;
	dY += speedY * dt;
	if (dX >= displacementX * 4) {
		dX = 0;
		if (movingLeft)
			movingLeft = false;
		else
			movingLeft = true;
	}
	if (dY >= displacementY) {
		dY = 0;
		if (movingDown) {
			movingDown = false;
		}
		else {
			movingDown = true;
		}
	}
}

void BeeBot::shootProjectile(float dt, float x, float targetX, float vol)
{
	if (projectileClk.getElapsedTime().asSeconds() > attackCooldown) {
		if (abs(enemyX - targetX) <= 1200.0f) {
			shootSound.setVolume(vol);
			shootSound.play();
		}
		projectileX = enemyX;
		projectileY = enemyY;
		projectileClk.restart();
	}
	else {
		projectileX += 150.0f * dt;
		projectileY += 150.0f * dt;
	}
}

Sprite& BeeBot::getNeedleSprite()
{
	return enemySprite;
}
