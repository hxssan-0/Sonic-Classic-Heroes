#pragma once
#include "Menu.h"
#include "Level1.h"
#include "Level2.h";
#include "Level3.h"
#include "BossLevel.h"
#include "Scoreboard.h"
using namespace sf;

class Game
{
private:
	RenderWindow window; //this is the main window for our game
	//the classes of which Game is composed
	Menu mainMenu;
	Levels* currentLvl;
	//flags to manage game states
	bool isMenu;
	bool isLevelMenu;
	bool isLevel1, isLevel2, isLevel3, isBossLevel;
	bool isLevelFinished;
	bool isGameOver;
	bool isGameFinished;
	bool isPaused;
	bool isOptions;
	bool isScoreBoard;
	bool isSaveMenu;
	bool isLoadMenu;
	bool isInstructions;
	//highscore is owned by Game to keep track across all levels
	int highscore;
	//save slots
	int numSlots;
	Scoreboard scoreboard;
	
	int globalVol;

	Font logoFont;
	Font optionsFont;
	Texture lvlSelectbgTex;
	Sprite lvlSelectbgSprite;
	Texture optionsMenubgTex;
	Texture instructionsbgTex;
	Sprite instructionsbgSprite;
	Sprite optionsMenubgSprite;
	Texture keyboardTex;
	Sprite keyboardSprite;
	Texture gameOverbgTex;
	Sprite gameOverbgSprite;
	Music lvlSelectMusic;
	//the sound when an option is selected
	SoundBuffer selectBuffer;
	Sound selectSound;
	//the sound when navigating the options
	SoundBuffer navigateBuffer;
	Sound navigateSound;
	SoundBuffer volumeSoundBuffer;
	Sound volumeSound;

public:
	Game(int width, int height);

	void displayMenu();

	void displayLevelSelect();

	void displayOptionsMenu();

	void displayInstructions();

	void displayPauseMenu();

	void gameOverScreen(int lvlScore);

	void levelFinishedScreen(int lvlScore);

	void runGame();


	~Game();

};