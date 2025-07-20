#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "TimeManager.h"
using namespace std;
using namespace sf;

TimeManager::TimeManager() : deltaTime(0.0f), totalTime(0.0f) {}

void TimeManager::update()
{
	deltaTime = clk.restart().asSeconds();
	totalTime += deltaTime;
}

float TimeManager::getDeltaTime() const
{
	return deltaTime;
}

float TimeManager::getTotalTime() const
{
	return totalTime;
}

