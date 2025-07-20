#pragma once
#include <iostream>
#include "SonicFactory.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void SonicFactory::createPlayer()
{
	sonic = new Sonic;
}

Players& SonicFactory::getPlayer()
{
	return *sonic;
}

//TODO
SonicFactory::~SonicFactory()
{

}