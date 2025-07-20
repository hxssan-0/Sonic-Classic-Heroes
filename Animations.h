#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Animations
{
private:
	Texture runSourceRightSonicTex;
	Sprite runSourceRightSonic;
	Texture runSourceLeftSonicTex;
	Sprite runSourceLeftSonic;
	//Sprite ring;
	IntRect rightRect;
	IntRect leftRect;
	//IntRect ringRect;
	Clock dt;
public:
	Animations();

	void initializeAnimations();

	void runRightSonic(RenderWindow& window, Sprite& playerSprite);

	void runLeftSonic(RenderWindow& window, Sprite& playerSprite);

};