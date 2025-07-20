#pragma once
#include <iostream>
#include "KnucklesFactory.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void KnucklesFactory::createPlayer()
{
	knuckles = new Knuckles;
}

Players& KnucklesFactory::getPlayer()
{
	return *knuckles;
}

//TODO
KnucklesFactory::~KnucklesFactory()
{

}