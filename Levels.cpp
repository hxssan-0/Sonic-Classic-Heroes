#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Levels.h"
using namespace std;
using namespace sf;

Levels::Levels(int nSprites, int lW, int lH, float g, float f, string musPath, int highscore, int& mVol) :
	cellSize(64), highscore(highscore), vol(mVol)
{
	lvlScore = 0;
	numBgSprites = nSprites;
	lvlBgTex = new Texture[numBgSprites];
	lvlBgSprites = new Sprite[numBgSprites];
	timeManager = new TimeManager;
	hud = new HUD;
	levelInit = false;
	//TODO --- SET LOOPS TO INITIALIZE ENEMIES, OBSTACLES AND COLLECTIBLES
	players = nullptr;
	defeatedEnemies = 0;
	enemies = nullptr;
	collectiblesFactories = new CollectiblesFactory*[3];
	collectiblesFactories[0] = new RingFactory;
	collectiblesFactories[1] = new HealthFactory;
	collectiblesFactories[2] = new BoostFactory;
	collectibles = new char* [lH];
	for (int i = 0; i < lH; i++) {
		collectibles[i] = new char[lW];
	}
	obstaclesPtr = new Obstacles(lW, lH);
	lvlWidth = lW * 64;
	lvlHeight = lH * 64;
	cellsX = lW;
	cellsY = lH;
	gravity = g;
	friction = f;
	lvlMusic.openFromFile(musPath);
	vol = mVol;
	lvlMusic.setVolume(vol);
	lvlMusic.play();
	lvlMusic.setLoop(true);
	activePlayerIndex = 0;
	playerActivity[0] = true;
	playerActivity[1] = false;
	playerActivity[2] = false;
	teamHealth = 3;
	collectedRings = numRings;
	damageBuffer.loadFromFile("Sprites\\Sounds\\Global\\Hurt.wav");
	damageSound.setBuffer(damageBuffer);
	damageSound.setVolume(vol);
	attackBuffer.loadFromFile("Sprites\\Sounds\\Global\\Destroy.wav");
	attackSound.setBuffer(attackBuffer);
	attackSound.setVolume(vol);

	lvlLost = false;
	lvlWon = false;

}

int Levels::getLvlScore() const
{
	return lvlScore;
}

bool Levels::getLvlWon() const
{
	return lvlWon;
}

bool Levels::getLvlLost() const
{
	return lvlLost;
}

//TODO
Levels::~Levels() {}
