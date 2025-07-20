#pragma once
#include <iostream>
#include "MotoBugFactory.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void MotoBugFactory::createEnemy(float eX, float eY)
{
	motobug = new MotoBug(eX, eY);
}

Enemies& MotoBugFactory::getEnemy()
{
	return *motobug;
}

//TODO
MotoBugFactory::~MotoBugFactory()
{

}