#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Menu.h"
using namespace std;
using namespace sf;

//constructor
Menu::Menu(int volume) : volume(volume)
{
	logoFont.loadFromFile("Fonts\\PressStart2P-Regular.ttf");
	optionsFont.loadFromFile("Fonts\\NiseSegaSonic.ttf");

	bgTex.loadFromFile("Backgrounds\\menuBg.jpg");
	bgSprite.setTexture(bgTex);

	title.setFont(logoFont);
	titleShadow.setFont(logoFont);
	title.setString("SONIC HEROES");
	titleShadow.setString("SONIC HEROES");
	title.setCharacterSize(72);
	titleShadow.setCharacterSize(72);
	title.setFillColor(Color(255, 150, 0));
	titleShadow.setFillColor(Color::Black);
	title.setOutlineColor(Color::Black);
	title.setOutlineThickness(4.0f);
	title.setStyle(Text::Bold);
	title.setPosition(200.0f, 100.f);
	titleShadow.setPosition(215.0f, 110.f);

	menuMusic.openFromFile("Data\\labrynth.ogg");
	menuMusic.setVolume(volume);
	menuMusic.play();
	menuMusic.setLoop(true);

	string optionNames[6] = {"New Game", "Options", "Instructions", "Continue", "Leaderboard", "Exit"};
	for (int i = 0; i < 6; i++) {
		options[i].setFont(optionsFont);
		optionShadows[i].setFont(optionsFont);
		options[i].setString(optionNames[i]);
		optionShadows[i].setString(optionNames[i]);
		options[i].setCharacterSize(52);
		optionShadows[i].setCharacterSize(52);
		options[i].setFillColor(Color(23, 86, 155)); //sonic blue rgb
		optionShadows[i].setFillColor(Color::Black);
		options[i].setOutlineColor(Color::Black);
		options[i].setOutlineThickness(2.0f);
		options[i].setPosition(50.0f, 200.0f + (100.0f * (i + 1)));
		optionShadows[i].setPosition(55.0f, 210.0f + (100.0f * (i + 1)));
	}

	optionIndex = 0;

	selectBuffer.loadFromFile("Sprites\\Sounds\\Global\\Select.wav");
	selectSound.setBuffer(selectBuffer);
	selectSound.setVolume(volume);
	navigateBuffer.loadFromFile("Sprites\\Sounds\\Global\\MenuButton.wav");
	navigateSound.setBuffer(navigateBuffer);
	navigateSound.setVolume(volume);
}

//the last four booleans will be passed by reference from the Game class to handle switching states
void Menu::runMenu(RenderWindow& window, bool& isMenu, bool& isLevel, bool& isOptions, bool& isScoreBoard, bool& isLoadMenu, bool& isInstructions, int volume)
{
	menuMusic.setVolume(volume);
	menuMusic.play();
	menuMusic.setLoop(true);
	Event e;
	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				//incrementing the option index but using mod operator to wrap around
				optionIndex = (optionIndex + 1) % 6;
				navigateSound.play();

			}
			else if (Keyboard::isKeyPressed(Keyboard::Up)) {
				optionIndex = (optionIndex - 1 + 6) % 6;
				navigateSound.play();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				isMenu = false;
				selectSound.play();
				if (optionIndex == 0) {
					isLevel = true;
				}
				else if (optionIndex == 1) {
					isOptions = true;
				}
				else if (optionIndex == 2) {
					isInstructions = true;
				}
				else if (optionIndex == 3) {
					isLoadMenu = true;
				}
				else if (optionIndex == 4) {
					isScoreBoard = true;
				}
				else if (optionIndex == 5) {
					exit(0);
				}
				menuMusic.stop();
				return;
			}
		}
		menuMusic.setVolume(volume);
		selectSound.setVolume(volume);
		navigateSound.setVolume(volume);

		//highlighting the selected option
		for (int i = 0; i < 6; i++) {
			if (i == optionIndex)
				options[i].setFillColor(Color::Red);
			else
				options[i].setFillColor(Color(23, 86, 155));
		}

		window.clear();

		window.draw(bgSprite);
		window.draw(titleShadow);
		window.draw(title);
		for (int i = 0; i < 6; i++) {
			window.draw(optionShadows[i]);
			window.draw(options[i]);
		}

		window.display();
	}
}