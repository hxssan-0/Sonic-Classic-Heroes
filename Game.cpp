#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Game.h"
using namespace std;
using namespace sf;

//constructor
Game::Game(int width, int height) : window(VideoMode(width, height), "Sonic the Hedgehog-OOP", Style::Close | Style::Resize | Style::Titlebar), mainMenu(30) {
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	//setting the main menu flag to true since that's where we want to start off with
	isMenu = true;
	isLevelMenu = false;
	isLevel1 = isLevel2 = isLevel3 = isBossLevel = false;
	isLevelFinished = false;
	isGameFinished = false;
	isGameOver = false;
	isPaused = false;
	isOptions = false;
	isScoreBoard = false;
	isSaveMenu = false;
	isLoadMenu = false;
	isInstructions = false;
	globalVol = 30;

	highscore = 0;

	//TODO --- save

	//lvl select menu
	logoFont.loadFromFile("Fonts\\PressStart2P-Regular.ttf");
	optionsFont.loadFromFile("Fonts\\NiseSegaSonic.ttf");
	lvlSelectbgTex.loadFromFile("Backgrounds\\level_select_bg.jpg");
	lvlSelectbgSprite.setTexture(lvlSelectbgTex);
	selectBuffer.loadFromFile("Sprites\\Sounds\\Global\\Select.wav");
	selectSound.setBuffer(selectBuffer);
	selectSound.setVolume(globalVol);
	navigateBuffer.loadFromFile("Sprites\\Sounds\\Global\\MenuButton.wav");
	navigateSound.setBuffer(navigateBuffer);
	navigateSound.setVolume(globalVol);

	optionsMenubgTex.loadFromFile("Backgrounds\\volume_select_bg.png");
	optionsMenubgSprite.setTexture(optionsMenubgTex);
	volumeSoundBuffer.loadFromFile("Sprites\\Sounds\\Global\\Ring.wav");
	volumeSound.setBuffer(volumeSoundBuffer);

	keyboardTex.loadFromFile("Sprites\\keyboard_sprite.png");
	keyboardSprite.setTexture(keyboardTex);

	instructionsbgTex.loadFromFile("Backgrounds\\instructions_bg_new.jpg");
	instructionsbgSprite.setTexture(instructionsbgTex);

	gameOverbgTex.loadFromFile("Backgrounds\\gameover_bg.png");
	gameOverbgSprite.setTexture(gameOverbgTex);
}

void Game::displayMenu()
{
	mainMenu.runMenu(window, isMenu, isLevelMenu, isOptions, isScoreBoard, isLoadMenu, isInstructions, globalVol);
}

//main game loop is here
void Game::runGame()
{
	Event e;
	while (window.isOpen())
	{

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}

		}
		window.clear();

		if (isMenu) {
			displayMenu();
		}
		else if (isLevelMenu) {
			displayLevelSelect();
		}
		else if (isOptions) {
			displayOptionsMenu();
		}
		else if (isInstructions) {
			displayInstructions();
		}
		else if (isScoreBoard) {
			scoreboard.display(window);
			isScoreBoard = false;
			isMenu = true;
		}
		else if (isLevel1) {
			if (!currentLvl) {
				currentLvl = new Level1(globalVol, highscore);
			}
			isLevel1 = true;
			currentLvl->runLevel(window);
			//pause screen will be activated if it has returned but level has neither been won nor lost
			if (!currentLvl->getLvlWon() && !currentLvl->getLvlLost()) {
				isPaused = true;
				displayPauseMenu();
				isPaused = false;
			}
			else if (currentLvl->getLvlWon() || currentLvl->getLvlLost()) {
				highscore = 0;
				if (currentLvl->getLvlLost()) {
					//game over screen, enter name etc
					gameOverScreen(currentLvl->getLvlScore());
				}
				else if (currentLvl->getLvlWon()) {
					//level trigger, display stats screen
					levelFinishedScreen(currentLvl->getLvlScore());
					/*isLevel2 = true;*/
				}
				isLevel1 = false;
				highscore += currentLvl->getLvlScore();
				if (currentLvl) {
					delete currentLvl;
					currentLvl = nullptr;
				}
			}
		}
		else if (isLevel2) {
			if (!currentLvl) {
				currentLvl = new Level2(globalVol, highscore);
			}
			isLevel2 = true;
			currentLvl->runLevel(window);
			//pause screen will be activated if it has returned but level has neither been won nor lost
			if (!currentLvl->getLvlWon() && !currentLvl->getLvlLost()) {
				isPaused = true;
				displayPauseMenu();
				isPaused = false;
			}
			else if (currentLvl->getLvlWon() || currentLvl->getLvlLost()) {
				highscore = 0;
				if (currentLvl->getLvlLost()) {
					//game over screen, enter name etc
					gameOverScreen(currentLvl->getLvlScore());
				}
				else if (currentLvl->getLvlWon()) {
					//level trigger, display stats screen
					levelFinishedScreen(currentLvl->getLvlScore());
				}
				isLevel2 = false;
				highscore += currentLvl->getLvlScore();
				if (currentLvl) {
					delete currentLvl;
					currentLvl = nullptr;
				}
			}
		}
		else if (isLevel3) {
			if (!currentLvl) {
				currentLvl = new Level3(globalVol, highscore);
			}
			isLevel3 = true;
			currentLvl->runLevel(window);
			//pause screen will be activated if it has returned but level has neither been won nor lost
			if (!currentLvl->getLvlWon() && !currentLvl->getLvlLost()) {
				isPaused = true;
				displayPauseMenu();
				isPaused = false;
			}
			else if (currentLvl->getLvlWon() || currentLvl->getLvlLost()) {
				highscore = 0;
				if (currentLvl->getLvlLost()) {
					//game over screen, enter name etc
					gameOverScreen(currentLvl->getLvlScore());
				}
				else if (currentLvl->getLvlWon()) {
					//level trigger, display stats screen
					levelFinishedScreen(currentLvl->getLvlScore());
				}
				isLevel3 = false;
				highscore += currentLvl->getLvlScore();
				if (currentLvl) {
					delete currentLvl;
					currentLvl = nullptr;
				}
			}
		}
		else if (isBossLevel) {
			if (!currentLvl) {
				currentLvl = new BossLevel(globalVol, highscore);
			}
			isBossLevel = true;
			currentLvl->runLevel(window);
			//pause screen will be activated if it has returned but level has neither been won nor lost
			if (!currentLvl->getLvlWon() && !currentLvl->getLvlLost()) {
				isPaused = true;
				displayPauseMenu();
				isPaused = false;
			}
			else if (currentLvl->getLvlWon() || currentLvl->getLvlLost()) {
				highscore = 0;
				if (currentLvl->getLvlLost()) {
					//game over screen, enter name etc
					gameOverScreen(currentLvl->getLvlScore());
				}
				else if (currentLvl->getLvlWon()) {
					//level trigger, display stats screen
					//game over screen
					levelFinishedScreen(currentLvl->getLvlScore());
				}
				isBossLevel = false;
				highscore += currentLvl->getLvlScore();
				if (currentLvl) {
					delete currentLvl;
					currentLvl = nullptr;
				}
			}
		}


		/*window.display();*/

	}
}

void Game::levelFinishedScreen(int lvlScore)
{
	//title, highscore, level score, save progress, menu, next level
	int numOptions = 3;
	int optionIndex = 0;

	lvlSelectMusic.openFromFile("Data\\labrynth.ogg");
	lvlSelectMusic.play();
	lvlSelectMusic.setVolume(globalVol);
	lvlSelectMusic.setLoop(true);

	Text titleText, titleShadowText;
	Text highscoreText, highscoreShadowText;
	Text lvlScoreText, lvlScoreShadowText;
	string options[3] = {"Next Level", "Save Progress", "Main Menu"};
	Text optionsText[3];
	Text optionShadows[3];
	titleText.setString("LEVEL COMPLETE!");
	titleShadowText.setString("LEVEL COMPLETE!");
	highscoreText.setString("High Score:" + to_string(highscore + lvlScore));
	highscoreShadowText.setString("High Score:" + to_string(highscore + lvlScore));
	lvlScoreText.setString("Level Score:" + to_string(lvlScore));
	lvlScoreShadowText.setString("Level Score:" + to_string(lvlScore));

	titleText.setFont(logoFont);
	titleText.setFont(logoFont);
	titleText.setCharacterSize(72);
	titleText.setCharacterSize(72);
	titleText.setFillColor(Color::Green);
	titleShadowText.setFillColor(Color::Black);
	titleText.setOutlineColor(Color::Black);
	titleText.setOutlineThickness(4.0f);
	titleText.setStyle(Text::Bold);
	titleText.setPosition(70.0f, 100.f);
	titleShadowText.setPosition(85.0f, 110.f);

	highscoreText.setFont(logoFont);
	highscoreText.setFont(logoFont);
	highscoreText.setCharacterSize(52);
	highscoreShadowText.setCharacterSize(52);
	highscoreText.setFillColor(Color::Cyan);
	highscoreShadowText.setFillColor(Color::Black);
	highscoreText.setOutlineColor(Color::Black);
	highscoreText.setOutlineThickness(4.0f);
	highscoreText.setStyle(Text::Bold);
	highscoreText.setPosition(200.0f, 200.f);
	highscoreShadowText.setPosition(215.0f, 210.f);

	lvlScoreText.setFont(logoFont);
	lvlScoreText.setFont(logoFont);
	lvlScoreText.setCharacterSize(52);
	lvlScoreShadowText.setCharacterSize(52);
	lvlScoreText.setFillColor(Color::Cyan);
	lvlScoreShadowText.setFillColor(Color::Black);
	lvlScoreText.setOutlineColor(Color::Black);
	lvlScoreText.setOutlineThickness(4.0f);
	lvlScoreText.setStyle(Text::Bold);
	lvlScoreText.setPosition(200.0f, 300.f);
	lvlScoreShadowText.setPosition(215.0f, 310.f);

	for (int i = 0; i < numOptions; i++) {
		optionsText[i].setFont(optionsFont);
		optionShadows[i].setFont(optionsFont);
		optionsText[i].setString(options[i]);
		optionShadows[i].setString(options[i]);
		optionsText[i].setCharacterSize(52);
		optionShadows[i].setCharacterSize(52);
		optionsText[i].setFillColor(Color::Yellow);
		optionShadows[i].setFillColor(Color::Black);
		optionsText[i].setOutlineColor(Color::Black);
		optionsText[i].setOutlineThickness(2.0f);
		optionsText[i].setPosition(50.0f, 600.0f + (75.0f * (i + 1)));
		optionShadows[i].setPosition(55.0f, 610.0f + (75.0f * (i + 1)));
	}

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
				optionIndex = (optionIndex + 1) % numOptions;
				navigateSound.play();

			}
			else if (Keyboard::isKeyPressed(Keyboard::Up)) {
				optionIndex = (optionIndex - 1 + numOptions) % numOptions;
				navigateSound.play();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				selectSound.play();
				if (optionIndex == 0) {
					if (isLevel1) {
						isLevel1 = false;
						isLevel2 = true;
					}
					else if (isLevel2) {
						isLevel2 = false;
						isLevel3 = true;
					}
					else if (isLevel3) {
						isLevel3 = false;
						isBossLevel = true;
					}
				}
				else if (optionIndex == 1) {
					//save state
				}
				else if (optionIndex == 2) {
					isMenu = true;
				}
				lvlSelectMusic.stop();
				return;
			}
		}
		lvlSelectMusic.setVolume(globalVol);
		selectSound.setVolume(globalVol);
		navigateSound.setVolume(globalVol);
		//highlighting the selected option
		for (int i = 0; i < numOptions; i++) {
			if (i == optionIndex) {
				optionsText[i].setFillColor(Color::Red);
			}
			else {
				optionsText[i].setFillColor(Color(23, 86, 155));
			}
		}

		window.clear();

		window.draw(gameOverbgSprite);
		window.draw(titleShadowText);
		window.draw(titleText);
		window.draw(highscoreShadowText);
		window.draw(highscoreText);
		window.draw(lvlScoreShadowText);
		window.draw(lvlScoreText);
		for (int i = 0; i < numOptions; i++) {
			window.draw(optionShadows[i]);
			window.draw(optionsText[i]);
		}

		window.display();

	}

}

void Game::gameOverScreen(int lvlScore)
{
	int numOptions = 2;
	int optionIndex = 0;

	lvlSelectMusic.openFromFile("Data\\labrynth.ogg");
	lvlSelectMusic.play();
	lvlSelectMusic.setVolume(globalVol);
	lvlSelectMusic.setLoop(true);

	Text titleText, titleShadowText;
	Text highscoreText, highscoreShadowText;
	Text lvlScoreText, lvlScoreShadowText;
	Text inputText, inputShadowText;
	Text returnText, returnShadowText;
	titleText.setString("GAME OVER!");
	titleShadowText.setString("GAME OVER!");
	highscoreText.setString("High Score:" + to_string(highscore + lvlScore));
	highscoreShadowText.setString("High Score:" + to_string(highscore + lvlScore));
	lvlScoreText.setString("Level Score:" + to_string(lvlScore));
	lvlScoreShadowText.setString("Level Score:" + to_string(lvlScore));
	inputText.setString("Enter Name");
	inputShadowText.setString("Enter Name");
	returnText.setString("Main Menu");
	returnShadowText.setString("Main Menu");


	titleText.setFont(logoFont);
	titleText.setFont(logoFont);
	titleText.setCharacterSize(72);
	titleText.setCharacterSize(72);
	titleText.setFillColor(Color::Red);
	titleShadowText.setFillColor(Color::Black);
	titleText.setOutlineColor(Color::Black);
	titleText.setOutlineThickness(4.0f);
	titleText.setStyle(Text::Bold);
	titleText.setPosition(200.0f, 100.f);
	titleShadowText.setPosition(215.0f, 110.f);

	highscoreText.setFont(logoFont);
	highscoreText.setFont(logoFont);
	highscoreText.setCharacterSize(52);
	highscoreShadowText.setCharacterSize(52);
	highscoreText.setFillColor(Color::Green);
	highscoreShadowText.setFillColor(Color::Black);
	highscoreText.setOutlineColor(Color::Black);
	highscoreText.setOutlineThickness(4.0f);
	highscoreText.setStyle(Text::Bold);
	highscoreText.setPosition(200.0f, 200.f);
	highscoreShadowText.setPosition(215.0f, 210.f);

	lvlScoreText.setFont(logoFont);
	lvlScoreText.setFont(logoFont);
	lvlScoreText.setCharacterSize(52);
	lvlScoreShadowText.setCharacterSize(52);
	lvlScoreText.setFillColor(Color::Green);
	lvlScoreShadowText.setFillColor(Color::Black);
	lvlScoreText.setOutlineColor(Color::Black);
	lvlScoreText.setOutlineThickness(4.0f);
	lvlScoreText.setStyle(Text::Bold);
	lvlScoreText.setPosition(200.0f, 300.f);
	lvlScoreShadowText.setPosition(215.0f, 310.f);

	inputText.setFont(optionsFont);
	inputText.setFont(optionsFont);
	inputText.setCharacterSize(30);
	inputText.setCharacterSize(30);
	inputShadowText.setFillColor(Color::Black);
	inputText.setOutlineColor(Color::Black);
	inputText.setOutlineThickness(2.0f);
	inputText.setPosition(50.0f, 700.0f);
	inputShadowText.setPosition(55.0f, 710.0f);

	returnText.setFont(optionsFont);
	returnText.setFont(optionsFont);
	returnText.setCharacterSize(30);
	returnText.setCharacterSize(30);
	returnShadowText.setFillColor(Color::Black);
	returnText.setOutlineColor(Color::Black);
	returnText.setOutlineThickness(2.0f);
	returnText.setPosition(50.0f, 750.0f);
	returnShadowText.setPosition(55.0f, 760.0f);

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
				optionIndex = (optionIndex + 1) % numOptions;
				navigateSound.play();

			}
			else if (Keyboard::isKeyPressed(Keyboard::Up)) {
				optionIndex = (optionIndex - 1 + numOptions) % numOptions;
				navigateSound.play();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				selectSound.play();
				if (optionIndex == 0) {
					//call scoreboard to input name
					scoreboard.update(highscore + lvlScore, window);
					isScoreBoard = false;
					isMenu = true;
				}
				else if (optionIndex == 1) {
					isMenu = true;
				}
				lvlSelectMusic.stop();
				return;
			}
		}
		lvlSelectMusic.setVolume(globalVol);
		selectSound.setVolume(globalVol);
		navigateSound.setVolume(globalVol);
		//highlighting the selected option

		if (optionIndex == 0) {
			inputText.setFillColor(Color::Red);
		}
		else {
			inputText.setFillColor(Color(23, 86, 155));
		}

		if (optionIndex == 1) {
			returnText.setFillColor(Color::Red);
		}
		else {
			returnText.setFillColor(Color(23, 86, 155));
		}

		window.clear();

		window.draw(gameOverbgSprite);
		window.draw(titleShadowText);
		window.draw(titleText);
		window.draw(highscoreShadowText);
		window.draw(highscoreText);
		window.draw(lvlScoreShadowText);
		window.draw(lvlScoreText);
		window.draw(inputText);
		window.draw(inputShadowText);
		window.draw(returnText);
		window.draw(returnShadowText);

		window.display();

	}
	
}

void Game::displayPauseMenu()
{
	//title, resume, options, save game, menu
	lvlSelectMusic.openFromFile("Data\\labrynth.ogg");
	lvlSelectMusic.play();
	lvlSelectMusic.setVolume(globalVol);
	lvlSelectMusic.setLoop(true);
	int optionsNum = 4;
	string title = "GAME PAUSED";
	string titleShadow = "GAME PAUSED";
	string* options = new string[optionsNum];
	string* optionsShadow = new string[optionsNum];
	Text titleText, titleShadowText;
	Text optionsText[4];
	Text optionsShadowText[4];
	int optionIndex = 0;
	options[0] = "Resume";
	options[1] = "Options";
	options[2] = "Save Progress";
	options[3] = "Back to Menu";
	optionsShadow[0] = "Resume";
	optionsShadow[1] = "Options";
	optionsShadow[2] = "Save Progress";
	optionsShadow[3] = "Back to Menu";

	titleText.setFont(logoFont);
	titleShadowText.setFont(logoFont);
	titleText.setString(title);
	titleShadowText.setString(title);
	titleText.setCharacterSize(72);
	titleShadowText.setCharacterSize(72);
	titleText.setFillColor(Color::Cyan);
	titleShadowText.setFillColor(Color::Black);
	titleText.setOutlineColor(Color::Black);
	titleText.setOutlineThickness(4.0f);
	titleText.setStyle(Text::Bold);
	titleText.setPosition(200.0f, 100.f);
	titleShadowText.setPosition(215.0f, 110.f);

	for (int i = 0; i < optionsNum; i++) {
		optionsText[i].setFont(optionsFont);
		optionsShadowText[i].setFont(optionsFont);
		optionsText[i].setString(options[i]);
		optionsShadowText[i].setString(options[i]);
		optionsText[i].setCharacterSize(52);
		optionsShadowText[i].setCharacterSize(52);
		optionsText[i].setFillColor(Color::Yellow); //sonic blue rgb
		optionsShadowText[i].setFillColor(Color::Black);
		optionsText[i].setOutlineColor(Color::Black);
		optionsText[i].setOutlineThickness(2.0f);
		optionsText[i].setPosition(50.0f, 250.0f + (100.0f * (i + 1)));
		optionsShadowText[i].setPosition(55.0f, 260.0f + (100.0f * (i + 1)));
	}

	optionIndex = 0;

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
				optionIndex = (optionIndex + 1) % optionsNum;
				navigateSound.play();

			}
			else if (Keyboard::isKeyPressed(Keyboard::Up)) {
				optionIndex = (optionIndex - 1 + optionsNum) % optionsNum;
				navigateSound.play();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				selectSound.play();
				if (optionIndex == 0) {
					lvlSelectMusic.stop();
					return;
				}
				else if (optionIndex == 1) {
					displayOptionsMenu();
				}
				else if (optionIndex == 2) {
					//save game
					lvlSelectMusic.stop();
					return;
				}
				else if (optionIndex == 3) {
					isMenu = true;
					if (isLevel1) {
						isLevel1 = false;
					}
					else if (isLevel2) {
						isLevel2 = false;
					}
					else if (isLevel3) {
						isLevel3 = false;
					}
					else if (isLevel3) {
						isLevel3 = false;
					}
					if (currentLvl) {
						delete currentLvl;
						currentLvl = nullptr;
					}
					lvlSelectMusic.stop();
					return;
				}
			}
		}
		lvlSelectMusic.setVolume(globalVol);
		selectSound.setVolume(globalVol);
		navigateSound.setVolume(globalVol);
		//highlighting the selected option
		for (int i = 0; i < optionsNum; i++) {
			if (i == optionIndex)
				optionsText[i].setFillColor(Color::Red);
			else
				optionsText[i].setFillColor(Color(23, 86, 155));
		}

		window.clear();

		window.draw(lvlSelectbgSprite);
		window.draw(titleShadowText);
		window.draw(titleText);
		for (int i = 0; i < optionsNum; i++) {
			window.draw(optionsShadowText[i]);
			window.draw(optionsText[i]);
		}

		window.display();

	}
}

void Game::displayLevelSelect()
{
	lvlSelectMusic.openFromFile("Data\\labrynth.ogg");
	lvlSelectMusic.play();
	lvlSelectMusic.setVolume(globalVol);
	lvlSelectMusic.setLoop(true);
	int optionsNum = 5;
	string title = "SELECT LEVEL";
	string titleShadow = "SELECT LEVEL";
	string* options = new string[optionsNum];
	string* optionsShadow = new string[optionsNum];
	Text titleText, titleShadowText;
	Text optionsText[5];
	Text optionsShadowText[5];
	int optionIndex = 0;
	options[0] = "1. Labyrinth Zone";
	options[1] = "2. Ice Cap Zone";
	options[2] = "3. Death Egg Zone";
	options[3] = "4. Boss Level";
	options[4] = "5. Back To Main Menu";
	optionsShadow[0] = "1. Labyrinth Zone";
	optionsShadow[1] = "2. Ice Cap Zone";
	optionsShadow[2] = "3. Death Egg Zone";
	optionsShadow[4] = "4. Boss Level";
	optionsShadow[4] = "5. Back To Main Menu";

	titleText.setFont(logoFont);
	titleShadowText.setFont(logoFont);
	titleText.setString(title);
	titleShadowText.setString(title);
	titleText.setCharacterSize(72);
	titleShadowText.setCharacterSize(72);
	titleText.setFillColor(Color(255, 150, 0));
	titleShadowText.setFillColor(Color::Black);
	titleText.setOutlineColor(Color::Black);
	titleText.setOutlineThickness(4.0f);
	titleText.setStyle(Text::Bold);
	titleText.setPosition(200.0f, 100.f);
	titleShadowText.setPosition(215.0f, 110.f);

	for (int i = 0; i < optionsNum; i++) {
		optionsText[i].setFont(optionsFont);
		optionsShadowText[i].setFont(optionsFont);
		optionsText[i].setString(options[i]);
		optionsShadowText[i].setString(options[i]);
		optionsText[i].setCharacterSize(52);
		optionsShadowText[i].setCharacterSize(52);
		optionsText[i].setFillColor(Color(23, 86, 155)); //sonic blue rgb
		optionsShadowText[i].setFillColor(Color::Black);
		optionsText[i].setOutlineColor(Color::Black);
		optionsText[i].setOutlineThickness(2.0f);
		optionsText[i].setPosition(50.0f, 250.0f + (100.0f * (i + 1)));
		optionsShadowText[i].setPosition(55.0f, 260.0f + (100.0f * (i + 1)));
	}

	optionIndex = 0;

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
				optionIndex = (optionIndex + 1) % optionsNum;
				navigateSound.play();

			}
			else if (Keyboard::isKeyPressed(Keyboard::Up)) {
				optionIndex = (optionIndex - 1 + optionsNum) % optionsNum;
				navigateSound.play();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				isLevelMenu = false;
				selectSound.play();
				if (optionIndex == 0) {
					isLevel1 = true;
				}
				else if (optionIndex == 1) {
					isLevel2 = true;
				}
				else if (optionIndex == 2) {
					isLevel3 = true;
				}
				else if (optionIndex == 3) {
					isBossLevel = true;
				}
				else if (optionIndex == 4) {
					isMenu = true;
				}
				lvlSelectMusic.stop();
				return;
			}
		}
		lvlSelectMusic.setVolume(globalVol);
		selectSound.setVolume(globalVol);
		navigateSound.setVolume(globalVol);
		//highlighting the selected option
		for (int i = 0; i < optionsNum; i++) {
			if (i == optionIndex)
				optionsText[i].setFillColor(Color::Red);
			else
				optionsText[i].setFillColor(Color(23, 86, 155));
		}

		window.clear();

		window.draw(lvlSelectbgSprite);
		window.draw(titleShadowText);
		window.draw(titleText);
		for (int i = 0; i < optionsNum; i++) {
			window.draw(optionsShadowText[i]);
			window.draw(optionsText[i]);
		}

		window.display();

	}
}

void Game::displayOptionsMenu()
{
	lvlSelectMusic.openFromFile("Data\\labrynth.ogg");
	lvlSelectMusic.play();
	lvlSelectMusic.setVolume(globalVol);
	lvlSelectMusic.setLoop(true);
	volumeSound.setVolume(globalVol);
	string title = "ADJUST VOLUME";
	string titleShadow = "ADJUST VOLUME";
	Text titleText, titleShadowText;
	Text volumeText, volumeShadowText;
	Text returnText, returnShadowText;
	bool volumeSelected = false;
	int optionIndex = 0;

	titleText.setFont(logoFont);
	titleShadowText.setFont(logoFont);
	titleText.setString(title);
	titleShadowText.setString(title);
	titleText.setCharacterSize(72);
	titleShadowText.setCharacterSize(72);
	titleText.setFillColor(Color(255, 150, 0));
	titleShadowText.setFillColor(Color::Black);
	titleText.setOutlineColor(Color::Black);
	titleText.setOutlineThickness(4.0f);
	titleText.setStyle(Text::Bold);
	titleText.setPosition(200.0f, 100.f);
	titleShadowText.setPosition(215.0f, 110.f);

	volumeText.setFont(optionsFont);
	volumeShadowText.setFont(optionsFont);
	volumeText.setString("Volume: " + to_string(globalVol));
	volumeShadowText.setString("Volume: " + to_string(globalVol));
	volumeText.setCharacterSize(52);
	volumeShadowText.setCharacterSize(52);
	volumeText.setFillColor(Color(23, 86, 155)); //sonic blue rgb
	volumeShadowText.setFillColor(Color::Black);
	volumeText.setOutlineColor(Color::Black);
	volumeText.setOutlineThickness(2.0f);
	volumeText.setPosition(50.0f, 250.0f + 100.0f);
	volumeShadowText.setPosition(55.0f, 260.0f + 100.0f);

	returnText.setFont(optionsFont);
	returnShadowText.setFont(optionsFont);
	returnText.setString("Back to Previous Screen");
	returnShadowText.setString("Back to Previous Screen");
	returnText.setCharacterSize(52);
	returnShadowText.setCharacterSize(52);
	returnText.setFillColor(Color(23, 86, 155)); //sonic blue rgb
	returnShadowText.setFillColor(Color::Black);
	returnText.setOutlineColor(Color::Black);
	returnText.setOutlineThickness(2.0f);
	returnText.setPosition(50.0f, 250.0f + 200.0f);
	returnShadowText.setPosition(55.0f, 260.0f + 200.0f);


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
				optionIndex = (optionIndex + 1) % 2;
				navigateSound.play();

			}
			else if (Keyboard::isKeyPressed(Keyboard::Up)) {
				optionIndex = (optionIndex - 1 + 2) % 2;
				navigateSound.play();
			}
			if (optionIndex == 0) {
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					volumeSound.play();
					globalVol = (globalVol - 1 + 100) % 100;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right)) {
					volumeSound.play();
					globalVol = (globalVol + 1) % 100;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				selectSound.play();
				if (optionIndex == 1) {
					isOptions = false;
					if (!isPaused)
						isMenu = true;
					else {
						displayPauseMenu();
					}
					lvlSelectMusic.stop();
					return;
				}
			}
		}
		lvlSelectMusic.setVolume(globalVol);
		volumeSound.setVolume(globalVol);
		selectSound.setVolume(globalVol);
		navigateSound.setVolume(globalVol);
		volumeText.setString("Volume: " + to_string(globalVol));
		volumeShadowText.setString("Volume: " + to_string(globalVol));
		//highlighting the selected option
		if (optionIndex == 0) {
			volumeText.setFillColor(Color::Red);
		}
		else
			volumeText.setFillColor(Color(23, 86, 155));

		if (optionIndex == 1)
			returnText.setFillColor(Color::Red);
		else
			returnText.setFillColor(Color(23, 86, 155));


		window.clear();

		window.draw(optionsMenubgSprite);
		window.draw(titleShadowText);
		window.draw(titleText);
		window.draw(volumeShadowText);
		window.draw(volumeText);
		window.draw(returnShadowText);
		window.draw(returnText);

		window.display();

	}
}

void Game::displayInstructions()
{
	lvlSelectMusic.openFromFile("Data\\labrynth.ogg");
	lvlSelectMusic.play();
	lvlSelectMusic.setVolume(globalVol);
	lvlSelectMusic.setLoop(true);
	keyboardSprite.setScale(2.0f, 2.0f);
	keyboardSprite.setPosition(150.0f, 200.0f);
	string title = "INSTRUCTIONS";
	string titleShadow = "INSTRUCTIONS";
	int numInstructions = 10;
	Text titleText, titleShadowText, returnText, returnShadowText;
	string* instructions = new string[numInstructions];
	string* instructionsShadow = new string[numInstructions];
	Text instructionsText[10]; //adjust
	Text instructionsShadowText[10];
	//write the instructions

	titleText.setFont(logoFont);
	titleShadowText.setFont(logoFont);
	titleText.setString(title);
	titleShadowText.setString(title);
	titleText.setCharacterSize(72);
	titleShadowText.setCharacterSize(72);
	titleText.setFillColor(Color(57, 255, 20));
	titleShadowText.setFillColor(Color(60, 0, 90));
	titleText.setOutlineColor(Color(0, 100, 0));
	titleText.setOutlineThickness(4.0f);
	titleText.setStyle(Text::Bold);
	titleText.setPosition(200.0f, 100.f);
	titleShadowText.setPosition(215.0f, 110.f);

	returnText.setFont(optionsFont);
	returnShadowText.setFont(optionsFont);
	returnText.setString("Back To Main Menu");
	returnShadowText.setString("Back To Main Menu");
	returnText.setCharacterSize(52);
	returnShadowText.setCharacterSize(52);
	returnText.setFillColor(Color::Red); //sonic blue rgb
	returnShadowText.setFillColor(Color::Black);
	returnText.setOutlineColor(Color::Black);
	returnText.setOutlineThickness(2.0f);
	returnText.setPosition(50.0f, 800.0f);
	returnShadowText.setPosition(55.0f, 810.0f);
	
	instructions[0] = "-> There are four levels you must complete to win";
	instructions[1] = "-> Press the left and right arrow keys to move";
	instructions[2] = "-> Press the up arrow key to jump";
	instructions[3] = "-> Press Z to switch players";
	instructions[4] = "-> As Tails, press Q to fly";
	instructions[5] = "-> When jumping or rolling, collide with enemies to hurt them";
	instructions[6] = "-> Beat all enemies and collect all rings to complete a level";
	instructions[7] = "-> Beware of traps such as spikes and pits";
	instructions[8] = "-> Never let your health fall below 3";
	instructions[9] = "-> Enjoy the game!";
	instructionsShadow[0] = "-> There are four levels you must complete to win";
	instructionsShadow[1] = "-> Press the left and right arrow keys to move";
	instructionsShadow[2] = "-> Press the up arrow key to jump";
	instructionsShadow[3] = "-> Press Z to switch players";
	instructionsShadow[4] = "-> As Tails, press Q to fly";
	instructionsShadow[5] = "-> When jumping or rolling, collide with enemies to hurt them";
	instructionsShadow[6] = "-> Beat all enemies and collect all rings to complete a level";
	instructionsShadow[7] = "-> Beware of traps such as spikes and pits";
	instructionsShadow[8] = "-> Never let your health fall below 3";
	instructionsShadow[9] = "-> Enjoy the game!";
	//instruction texts draws here
	for (int i = 0; i < numInstructions; i++) {
		instructionsText[i].setFont(optionsFont);
		instructionsShadowText[i].setFont(optionsFont);
		instructionsText[i].setString(instructions[i]);
		instructionsShadowText[i].setString(instructions[i]);
		instructionsText[i].setCharacterSize(20);
		instructionsShadowText[i].setCharacterSize(20);
		instructionsText[i].setFillColor(Color::Yellow);
		instructionsShadowText[i].setFillColor(Color::Black);
		instructionsText[i].setOutlineColor(Color::Black);
		instructionsText[i].setOutlineThickness(1.2f);
		instructionsText[i].setPosition(50.0f, 550.0f + (20.0f * (i + 1)));
		instructionsShadowText[i].setPosition(55.0f, 552.0f + (20.0f * (i + 1)));
	}


	Event e;
	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				isInstructions = false;
				isMenu = true;
				selectSound.play();
				lvlSelectMusic.stop();
				return;
			}
		}

		window.clear();

		window.draw(instructionsbgSprite);
		window.draw(keyboardSprite);
		window.draw(titleShadowText);
		window.draw(titleText);
		for (int i = 0; i < numInstructions; i++) {
			window.draw(instructionsShadowText[i]);
			window.draw(instructionsText[i]);
		}
		window.draw(returnShadowText);
		window.draw(returnText);

		window.display();

	}
}

Game::~Game()
{
	
}