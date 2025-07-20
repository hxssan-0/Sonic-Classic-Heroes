#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "RingFactory.h"


void RingFactory::createCollectible(int x, int y)
{
	ring = new Ring(x, y);
}
Collectibles& RingFactory::getCollectible()
{
	return *ring;
}

RingFactory::~RingFactory()
{
	delete ring;
}
