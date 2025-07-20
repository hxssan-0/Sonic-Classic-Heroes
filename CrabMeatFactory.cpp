#pragma once
#include <iostream>
#include "CrabMeatFactory.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void CrabMeatFactory::createEnemy(float eX, float eY)
{
	crabmeat = new CrabMeat(eX, eY);
}

Enemies& CrabMeatFactory::getEnemy()
{
	return *crabmeat;
}

//TODO
CrabMeatFactory::~CrabMeatFactory()
{

}