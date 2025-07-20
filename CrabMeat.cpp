#pragma once
#include <iostream>
#include "CrabMeat.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;


//TODO --- adjust speeds, ranges and coordinates
CrabMeat::CrabMeat(float eX, float eY) : Crawlers(1, 150.0f, 0, eX, eY, 200.0f, 0, 10.0f, true, "Sprites\\crabmeat_sprite.png", 2.5f, 2.5f, 42, 31)
{
	movingLeft = true;
	projectileSpeedX = 150.0f;
	projectileSpeedY = 0.0f; //adjust
	projectileTex.loadFromFile("Sprites\\projectile_sprite.png");
	projectileSprite.setTexture(projectileTex);
	projectileSprite.setScale(3.0, 3.0);
	projectileSprite.setColor(Color::Blue);
	projectileSprite.setPosition(enemyX, enemyY);
	projectileClk.restart();
	shootBuffer.loadFromFile("Sprites\\Sounds\\Global\\Explosion.wav");
	shootSound.setBuffer(shootBuffer);
}

void CrabMeat::update(float dt, float x, RenderWindow& window, float targetX, float targetY, float gravity, float vol, char** lvl)
{
	moveEnemy(dt, targetX);
	shootProjectile(dt, x, targetX, gravity, vol);
	enemySprite.setPosition(x, enemyY);
}

void CrabMeat::moveEnemy(float dt, float targetX, float targetY)
{

	if (movingLeft) {
		enemyX -= speedX * dt;
	}
	else {
		enemyX += speedX * dt;
	}

	dX += speedX * dt;
	if (dX >= displacementX) {
		dX = 0;
		if (movingLeft)
			movingLeft = false;
		else
			movingLeft = true;
	}
}

void CrabMeat::shootProjectile(float dt, float x, float targetX, float gravity, float vol)
{
	//using projectile motion equations
	if (projectileClk.getElapsedTime().asSeconds() > attackCooldown) {
		if (abs(enemyX - targetX) <= 1200.0f) {
			shootSound.setVolume(vol);
			shootSound.play();
		}
		projectileX = enemyX;
		projectileY = enemyY;
		projectileSpeedY = -200.0f;
		projectileClk.restart();
	}
	else {
		projectileSpeedY += gravity * 98 * dt;
		projectileX += projectileSpeedX * dt;
		projectileY += projectileSpeedY * dt;
	}
}

Sprite& CrabMeat::getNeedleSprite()
{
	return enemySprite;
}