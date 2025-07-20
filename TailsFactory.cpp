#pragma once
#include <iostream>
#include "TailsFactory.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void TailsFactory::createPlayer()
{
	tails = new Tails;
}

Players& TailsFactory::getPlayer()
{
	return *tails;
}

//TODO
TailsFactory::~TailsFactory()
{

}