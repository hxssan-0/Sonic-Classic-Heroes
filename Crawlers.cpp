#pragma once
#include <iostream>
#include "Crawlers.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;


Crawlers::Crawlers(int hp, float sX, float sY, float eX, float eY, float disX, float disY, float cooldown, bool shoots, string enemyTexPath, float sclX, float sclY, float imgX, float imgY) : Enemies(hp, sX, sY, eX, eY, disX, disY, cooldown, shoots, enemyTexPath, sclX, sclY, imgX, imgY) {}

Sprite& Crawlers::getNeedleSprite()
{
	return enemySprite;
}