#pragma once
#include<iostream>
#include "Health.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;


Health::Health(float x, float y) : Collectibles(x, y)
{
	itemTex.loadFromFile("Sprites\\heart_sprite.png");
	itemSprite.setTexture(itemTex);
}