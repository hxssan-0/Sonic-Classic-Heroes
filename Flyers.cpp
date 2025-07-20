#pragma once
#include <iostream>
#include "Flyers.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;


Flyers::Flyers(int hp, float sX, float sY, float eX, float eY, float disX, float disY, float cooldown, bool shoots, string enemyTexPath, float sclX, float sclY, float imgX, float imgY) : Enemies(hp, sX, sY, eX, eY, disX, disY, cooldown, shoots, enemyTexPath,sclX, sclY, imgX, imgY) {}

Sprite& Flyers::getNeedleSprite()
{
	return enemySprite;
}