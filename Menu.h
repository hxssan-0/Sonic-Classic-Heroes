#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

class Menu
{
private:
	Font logoFont;
	Font optionsFont;
	Texture bgTex;
	Sprite bgSprite;
	Text title;
	Text titleShadow;
	Text options[6]; //only 4 options required for the main menu
	Text optionShadows[6];
	int optionIndex;
	Music menuMusic;
	int volume;
	//the sound when an option is selected
	SoundBuffer selectBuffer;
	Sound selectSound;
	//the sound when navigating the options
	SoundBuffer navigateBuffer;
	Sound navigateSound;

public:
	Menu(int volume);

	void runMenu(RenderWindow&, bool&, bool&, bool&, bool&, bool&, bool&, int);
};