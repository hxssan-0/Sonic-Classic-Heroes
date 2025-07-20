#pragma once
#include <iostream>
#include "BeeBotFactory.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void BeeBotFactory::createEnemy(float eX, float eY)
{
	beebot = new BeeBot(eX, eY);
}

Enemies& BeeBotFactory::getEnemy()
{
	return *beebot;
}

//TODO
BeeBotFactory::~BeeBotFactory()
{

}