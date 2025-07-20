#pragma once
#include<iostream>
#include "Ring.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;


Ring::Ring(float x, float y) : Collectibles(x, y)
{
	itemTex.loadFromFile("Sprites\\ring_sprite.png");
	itemSprite.setTexture(itemTex);
}