#pragma once
#include <iostream>
#include "Scoreboard.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

Scoreboard::Scoreboard()
{
	font.loadFromFile("Fonts\\NiseSegaSonic.ttf");
	inputTex.loadFromFile("Backgrounds\\name_bg.jpg");
	inputSprite.setTexture(inputTex);
}

void Scoreboard::update(int score, RenderWindow& window)
{
	ofstream highscores("Data\\highscores.txt", ios::app);

	Text enterText;
	enterText.setFont(font);
	enterText.setString("Enter Your Name (15 Characters Max)");
	enterText.setCharacterSize(30);
	enterText.setFillColor(Color::Cyan);
	enterText.setPosition(180.0f, 100.0f);
	enterText.setOutlineColor(Color::Black);
	enterText.setOutlineThickness(2.0f);
	Text nameText;
	nameText.setFont(font);
	nameText.setCharacterSize(30);
	nameText.setString("");
	nameText.setPosition(180.0f, 200.0f);
	nameText.setFillColor(Color::Yellow);
	nameText.setOutlineColor(Color::Black);
	nameText.setOutlineThickness(2.0f);

	//going to use Event::TextEntered to input names on screen
	char name[16] = "\0";
	int index = 0;
	bool entered = false;
	Event e;
	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
			{
				window.close();
			}
			else if (e.type == Event::TextEntered && !entered) {
				if (inputClk.getElapsedTime().asSeconds() > 0.05) {
					//backspace character will allow deleting
					if (e.text.unicode == '\b') {
						if (index > 0) {
							index--;
							name[index] = '\0';
						}
					}
					else if (Keyboard::isKeyPressed(Keyboard::Equal)) {
						entered = true;
						display(window);
					}
					else if (index < 16) {
						name[index] = char(e.text.unicode);
						index++;
						name[index] = '\0';
					}
					inputClk.restart();
				}
			}
		}
		nameText.setString(name);
		window.clear();
		window.draw(inputSprite);
		window.draw(enterText);
		window.draw(nameText);
		window.display();
		if (entered)
			break;

	}
	//checking if the name is already present in the file to update the score
	ifstream checkFile("Data\\highscores.txt");
	bool found = false;
	int count = 0;
	while (count < 50 && checkFile >> names[count] && checkFile >> scores[count]) {
		count++;
	}
	checkFile.close();
	string name_string = string(name);
	for (int i = 0; i < count; i++) {
		if (names[i] == name_string) {
			found = true;
			if (scores[i] < score) {
				scores[i] = score;
				break;
			}
		}
	}
	if (!found) {
		highscores << name << ' ' << score;
		highscores.close();
	}
	else {
		ofstream rewrite("Data\\highscores.txt");
		for (int i = 0; i < count; i++) {
			rewrite << names[i] << ' ' << scores[i];
		}
		rewrite.close();
	}
}

void Scoreboard::display(RenderWindow& window)
{
	ifstream highscores("Data\\highscores.txt");
	//only checking upto 50 entries since player count is unknown
	int count = 0;
	while (count < 50 && highscores >> names[count] && highscores >> scores[count]) {
		count++;
	}
	highscores.close();

	//now using bubble sort on the extracted data
	for (int i = count - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			if (scores[j] < scores[j + 1]) {
				int temp1 = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = temp1;

				//swapping the names too
				string temp2 = names[j];
				names[j] = names[j + 1];
				names[j + 1] = temp2;
			}
		}
	}

	Text title;
	title.setFont(font);
	title.setString("LEADERBOARD");
	title.setFillColor(Color::Yellow);
	title.setCharacterSize(72);
	title.setOutlineColor(Color::Black);
	title.setOutlineThickness(2.0f);
	title.setPosition(260.0f, 100.0f);

	Text returnText;
	returnText.setFont(font);
	returnText.setString("Back to Menu");
	returnText.setFillColor(Color::Blue);
	returnText.setCharacterSize(20);
	returnText.setPosition(50.0f, 800.0f);

	Text rankings[10];

	for (int i = 0; i < 10; i++) {
		rankings[i].setFont(font);
		rankings[i].setString(to_string(i + 1) + ". " + names[i] + " - " + to_string(scores[i]));
		rankings[i].setCharacterSize(30);
		if (i == 0) {
			rankings[i].setFillColor(Color(255, 215, 0)); //gold for first place, silver for 2nd and bronze for 3rd
		}
		else if (i == 1) {
			rankings[i].setFillColor(Color(192, 192, 192));
		}
		else if (i == 2) {
			rankings[i].setFillColor(Color(110, 77, 37));
		}
		else {
			rankings[i].setFillColor(Color::White);
		}
		rankings[i].setOutlineColor(Color::Black);
		rankings[i].setOutlineThickness(1.5f);
		rankings[i].setPosition(50.0f, 250.0f + (50.0f * (i + 1)));
	}

	Event e;
	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
			{
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				return;
			}
		}
		window.clear();
		window.draw(title);
		for (int i = 0; i < 10; i++)
			window.draw(rankings[i]);
		window.draw(returnText);
		window.display();
	}
}