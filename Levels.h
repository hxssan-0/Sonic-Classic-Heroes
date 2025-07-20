#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "TimeManager.h"
#include "SonicFactory.h"
#include "TailsFactory.h"
#include "KnucklesFactory.h"
#include "BatBrainFactory.h"
#include "BeeBotFactory.h"
#include "MotoBugFactory.h"
#include "CrabMeatFactory.h"
#include "RingFactory.h"
#include "HealthFactory.h"
#include "BoostFactory.h"
#include "Obstacles.h"
#include "Camera.h"
#include "HUD.h"
#include "CollisionDetection.h"
using namespace std;
using namespace sf;

class Levels
{
protected:
	int lvlScore;
	int highscore;
	bool levelInit;
	Texture* lvlBgTex;
	int numBgSprites;
	Sprite* lvlBgSprites;
	TimeManager* timeManager;
	PlayerFactory** players;
	int activePlayerIndex;
	bool playerActivity[3];
	int numEnemies;
	int defeatedEnemies;
	EnemyFactory** enemies;
	int numCollectibles;
	int numRings;
	int numLives;
	int numBoosts;
	int collectedRings;
	CollectiblesFactory** collectiblesFactories;
	char** collectibles;
	Obstacles* obstaclesPtr;
	Camera* camera;
	HUD* hud;
	int lvlWidth;
	int lvlHeight;
	int cellsX;
	int cellsY;
	float gravity;
	float friction;
	Music lvlMusic;
	int& vol;
	const int cellSize;
	Texture wallTex1;
	Sprite wallSprite1;
	Texture platformTex;
	Sprite platformSprite;
	Texture spikeTex;
	Sprite spikeSprite;
	Texture breakableWallTex;
	Sprite breakableWallSprite;
	int teamHealth;
	float levelTime;
	SoundBuffer damageBuffer;
	Sound damageSound;
	SoundBuffer attackBuffer;
	Sound attackSound;
	bool lvlLost, lvlWon;


public:
	Levels(int nSprites, int lW, int lH, float g, float f, string musPath, int highscore, int& mVol); //last one is default arg

	virtual ~Levels();

	virtual void createBackground() = 0;

	virtual void createObstacles() = 0;

	virtual void createCollectibles() = 0;

	virtual void drawCollectibles(RenderWindow&) = 0;

	virtual void drawObstacles(RenderWindow&) = 0;

	virtual bool isLevelWon() = 0;

	virtual bool isLevelLost() = 0;

	virtual void followActivePlayer(int i, RenderWindow& window) = 0;

	virtual void flyWithTails(int i, RenderWindow& window) = 0;

	int getLvlScore() const;

	bool getLvlWon() const;

	bool getLvlLost() const;

	virtual void runLevel(RenderWindow&) = 0;
};