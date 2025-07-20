#pragma once
#include <iostream>
#include "FlyerFactory.h"
#include "EggStinger.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class EggStingerFactory : public FlyerFactory
{
private:
	EggStinger* eggstinger;
public:
	virtual void createEnemy(float eX, float eY);

	virtual Enemies& getEnemy();

	~EggStingerFactory();
};
