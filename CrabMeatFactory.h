#pragma once
#include <iostream>
#include "CrawlerFactory.h"
#include "CrabMeat.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class CrabMeatFactory : public CrawlerFactory
{
private:
	CrabMeat* crabmeat;
public:
	virtual void createEnemy(float eX, float eY);

	virtual Enemies& getEnemy();

	~CrabMeatFactory();
};
