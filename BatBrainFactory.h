#pragma once
#include <iostream>
#include "FlyerFactory.h"
#include "BatBrain.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class BatBrainFactory : public FlyerFactory
{
private:
	BatBrain* batbrain;
public:
	virtual void createEnemy(float eX, float eY);

	virtual Enemies& getEnemy();

	~BatBrainFactory();
};