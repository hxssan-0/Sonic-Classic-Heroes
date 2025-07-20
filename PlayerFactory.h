#pragma once
#include <iostream>
#include "Players.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class PlayerFactory
{
public:

	virtual void createPlayer() = 0;

	virtual Players& getPlayer() = 0;

	virtual ~PlayerFactory();
};
