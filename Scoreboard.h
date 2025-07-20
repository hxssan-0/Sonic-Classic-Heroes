#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Scoreboard
{
private:
	string names[50];
	int scores[50];
	Font font;
	Clock inputClk;
	Texture inputTex;
	Sprite inputSprite;
	Texture displayTex;
	Sprite displaySprite;

public:
	Scoreboard();

	void update(int score, RenderWindow&);

	void display(RenderWindow&);
};

