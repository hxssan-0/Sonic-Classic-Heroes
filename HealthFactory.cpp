#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "HealthFactory.h"


void HealthFactory::createCollectible(int x, int y)
{
	health = new Health(x, y);
}
Collectibles& HealthFactory::getCollectible()
{
	return *health;
}

HealthFactory::~HealthFactory()
{
	delete health;
}
