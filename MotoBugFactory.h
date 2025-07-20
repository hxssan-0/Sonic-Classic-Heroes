#pragma once
#include <iostream>
#include "CrawlerFactory.h"
#include "MotoBug.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class MotoBugFactory : public CrawlerFactory
{
private:
	MotoBug* motobug;
public:
	virtual void createEnemy(float eX, float eY);

	virtual Enemies& getEnemy();

	~MotoBugFactory();
};