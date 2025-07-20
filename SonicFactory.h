#pragma once
#include <iostream>
#include "PlayerFactory.h"
#include "Sonic.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class SonicFactory : public PlayerFactory
{
private:
	Sonic* sonic;
public:
	virtual void createPlayer();

	virtual Players& getPlayer();

	~SonicFactory();
};