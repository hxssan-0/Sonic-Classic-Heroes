#pragma once
#include <iostream>
#include "BatBrainFactory.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void BatBrainFactory::createEnemy(float eX, float eY)
{
	batbrain = new BatBrain(eX, eY);
}

Enemies& BatBrainFactory::getEnemy()
{
	return *batbrain;
}

//TODO
BatBrainFactory::~BatBrainFactory()
{

}