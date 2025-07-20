#pragma once
#include<iostream>
#include "Collectibles.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

Collectibles::Collectibles(int x, int y) : x(x), y(y) {}

int Collectibles::getX() const
{
	return x;
}
int Collectibles::getY() const
{
	return y;
}
void Collectibles::setX(int x)
{
	this->x = x;
}
void Collectibles::setY(int y)
{
	this->y = y;
}

Sprite& Collectibles::getSprite()
{
	return itemSprite;
}