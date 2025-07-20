#pragma once
#include <iostream>
#include "Enemies.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

Enemies::Enemies(int hp, float sX, float sY, float eX, float eY, float disX, float disY, float cooldown, bool shoots, string enemyTexPath, float sclX, float sclY, float imgX, float imgY) {
	health = hp;
	speedX = sX;
	speedY = sY;
	enemyX = eX;
	enemyY = eY;
	width = imgX * sclX;
	height = imgY * sclY;
	displacementX = disX;
	displacementY = disY;
	dX = 0;
	dY = 0;
	scaleX = sclX;
	scaleY = sclY;
	enemyWidth = scaleX * imgX;
	enemyHeight = scaleY * imgY;
	attackCooldown = cooldown;
	shootsProjectiles = shoots;
	if (shootsProjectiles) {
		projectileActive = false;
	}
	enemyActive = true;
	char** dummy = nullptr;
	char** dummy2 = nullptr;
	cd = new CollisionDetection(8 * abs(sclX), 5 * abs(sclY), width, height, 64, dummy, dummy2);
	enemyTex.loadFromFile(enemyTexPath);
	enemySprite.setTexture(enemyTex);
	enemySprite.setScale(scaleX, scaleY);
	enemySprite.setPosition(enemyX, enemyY);
}

void Enemies::decHealth()
{
	if (health - 1 >= 0)
		health--;
}

float Enemies::getAttackCooldown() const
{
	return attackCooldown;
}

float Enemies::getEnemyX() const
{
	return enemyX;
}

float Enemies::getEnemyY() const
{
	return enemyY;
}

float Enemies::getProjectileX() const
{
	return projectileX;
}

float Enemies::getProjectileY() const
{
	return projectileY;
}

bool Enemies::getProjectileStatus() const
{
	return projectileActive;
}

int Enemies::getHealth() const
{
	return health;
}

bool Enemies::doesShootProjectiles() const
{
	return shootsProjectiles;
}

Sprite& Enemies::getSprite()
{
	return enemySprite;
}

float Enemies::getEnemyWidth() const
{
	return enemyWidth;
}

float Enemies::getEnemyHeight() const
{
	return enemyHeight;
}

Sprite& Enemies::getNeedleSprite()
{
	return enemySprite;
}

Sprite& Enemies::getProjectileSprite()
{
	return projectileSprite;
}

CollisionDetection& Enemies::getCD()
{
	return *cd;
}

bool Enemies::getEnemyActivity() const
{
	return enemyActive;
}

void Enemies::setEnemyActivity(bool b)
{
	enemyActive = b;
}