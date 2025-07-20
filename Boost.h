#pragma once
#include<iostream>
#include "Collectibles.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Boost : public Collectibles
{
public:
	Boost(float x, float y);
};
