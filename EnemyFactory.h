#pragma once
#include <iostream>
#include "Enemies.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class EnemyFactory
{
public:

	virtual void createEnemy(float eX, float eY) = 0;

	virtual Enemies& getEnemy() = 0;

	virtual ~EnemyFactory();
};
