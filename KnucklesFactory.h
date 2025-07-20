#pragma once
#include <iostream>
#include "PlayerFactory.h"
#include "Knuckles.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class KnucklesFactory : public PlayerFactory
{
private:
	Knuckles* knuckles;
public:
	virtual void createPlayer();

	virtual Players& getPlayer();

	~KnucklesFactory();
};