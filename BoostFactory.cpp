#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "BoostFactory.h"


void BoostFactory::createCollectible(int x, int y)
{
	boost = new Boost(x, y);
}
Collectibles& BoostFactory::getCollectible()
{
	return *boost;
}

BoostFactory::~BoostFactory()
{
	delete boost;
}
