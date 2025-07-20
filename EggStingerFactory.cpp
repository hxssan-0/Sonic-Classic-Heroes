#pragma once
#include <iostream>
#include "EggStingerFactory.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void EggStingerFactory::createEnemy(float eX, float eY)
{
	eggstinger = new EggStinger(eX, eY);
}

Enemies& EggStingerFactory::getEnemy()
{
	return *eggstinger;
}

//TODO
EggStingerFactory::~EggStingerFactory()
{

}