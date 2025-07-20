#pragma once
#include<iostream>
#include "Boost.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;


Boost::Boost(float x, float y) : Collectibles(x, y)
{
	itemTex.loadFromFile("Sprites\\boost_sprite.png");
	itemSprite.setTexture(itemTex);
}