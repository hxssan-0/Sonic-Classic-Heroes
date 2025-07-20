#pragma once
#include <iostream>
#include "PlayerFactory.h"
#include "Tails.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class TailsFactory : public PlayerFactory
{
private:
	Tails* tails;
public:
	virtual void createPlayer();

	virtual Players& getPlayer();

	~TailsFactory();
};
