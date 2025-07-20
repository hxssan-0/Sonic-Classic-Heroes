#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

//renamed it since it was clashing with sf::Time

class TimeManager
{
private:
	Clock clk;
	float deltaTime;
	float totalTime;
public:
	TimeManager();

	void update();

	float getDeltaTime() const;

	float getTotalTime() const;
};