#pragma once
#include <iostream>
#include "FlyerFactory.h"
#include "BeeBot.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class BeeBotFactory : public FlyerFactory
{
private:
	BeeBot* beebot;
public:
	virtual void createEnemy(float eX, float eY);

	virtual Enemies& getEnemy();

	~BeeBotFactory();
};
