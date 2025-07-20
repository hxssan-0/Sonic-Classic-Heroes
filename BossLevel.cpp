#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "BossLevel.h"
using namespace std;
using namespace sf;

//TODO
BossLevel::BossLevel(int& vol, int highscore) : Levels(1, 25, 14, 1.0f, 0.95f, "", highscore, vol) {
	lvlBgTex = new Texture[numBgSprites];
	lvlBgSprites = new Sprite[numBgSprites];
	players = new PlayerFactory * [1];
	players[0] = new SonicFactory;
	players[0]->createPlayer();
	players[0]->getPlayer().setModifiers(gravity, friction);
	//adjust according to number and types of enemies
	numEnemies = 1; //adjust
	enemies = new EnemyFactory * [numEnemies];
	levelTime = 120.0f; //2 mins for this level
	teamHealth = 9;

}

//TODO
BossLevel::~BossLevel() {}

//TODO
void BossLevel::createBackground() {
	lvlBgTex[0].loadFromFile("Backgrounds\\lvl4_bg.png");
	float* left = new float[numBgSprites];
	float* right = new float[numBgSprites];
	float pi = 600.0f;
	float* player = &pi;
	for (int i = 0; i < numBgSprites; i++) {
		lvlBgSprites[i].setTexture(lvlBgTex[i]);
		left[i] = 1200 * i;
		right[i] = left[i] + 1200;
	}

	camera = new Camera(numBgSprites, left, right, player, lvlBgSprites);
}

void BossLevel::createObstacles()
{
	wallTex1.loadFromFile("Sprites\\moon_block_sprite.png");
	wallSprite1.setTexture(wallTex1);
	platformTex.loadFromFile("Data\\brick2.png");
	platformSprite.setTexture(platformTex);
	spikeTex.loadFromFile("Data\\spike.png");
	spikeSprite.setTexture(spikeTex);
	breakableWallTex.loadFromFile("Sprites\\breakable_wall_sprite.png");
	breakableWallSprite.setTexture(breakableWallTex);

	for (int i = 0; i < 20; i++) {
		obstaclesPtr->createObstacle(11, i, 'w');
	}
	//ground

	players[0]->getPlayer().createCollisionDetection(obstaclesPtr->getObstacles(), collectibles);
}

void BossLevel::createCollectibles()
{

}

void BossLevel::createEnemies()
{
	enemies[0] = new EggStingerFactory;
	enemies[0]->createEnemy(600.0f, 300.0f);
}

void BossLevel::drawCollectibles(RenderWindow& window)
{
}

void BossLevel::drawObstacles(RenderWindow& window)
{
	for (int i = 0; i < 20; i++) {
		if (obstaclesPtr->checkObstacle(11, i, 'w')) {
			wallSprite1.setPosition(i * cellSize, 11 * cellSize);
			window.draw(wallSprite1);
		}
	}
}

//TODO
bool BossLevel::isLevelLost()
{
	if (timeManager->getTotalTime() > levelTime || teamHealth <= 0 || players[activePlayerIndex]->getPlayer().didFallInPit()) {
		lvlLost = true;
		return true;
	}
	lvlLost = false;
	return false;
}

//TODO
bool BossLevel::isLevelWon() {
	if ((defeatedEnemies == numEnemies) && (collectedRings == numRings)) {
		lvlWon = true;
		return true;
	}
	lvlWon = false;
	return false;
}

void BossLevel::runLevel(RenderWindow& window) {

	if (!levelInit) {
		createBackground();
		createObstacles();
		createEnemies();
		levelInit = true;
	}

	Event e;
	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
			{
				window.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Z))
				switchActivePlayer();

			//pause screen
			if (Keyboard::isKeyPressed(Keyboard::P))
				return;
		}

		window.clear();

		//back to game class loop
		if (isLevelLost() || isLevelWon()) {
			return;
		}

		//changing sound volumes incase volume was modified
		attackSound.setVolume(vol);
		damageSound.setVolume(vol);

		//time manager updated every frame
		timeManager->update();

		for (int i = 0; i < numBgSprites; i++) {
			window.draw(lvlBgSprites[i]);
		}

		//camera update
		camera->runCamera(window, players[activePlayerIndex]->getPlayer().getX(), cellsX);

		//drawing obstacles
		drawObstacles(window);

		//calculating the score
		lvlScore = (defeatedEnemies * 200) + (collectedRings * 50);
		int tempScore = highscore + lvlScore;

		//displaying hud
		hud->updateHUD(tempScore, timeManager->getTotalTime(), teamHealth, collectedRings, players[activePlayerIndex]->getPlayer().getInvincibilityStatus(), levelTime, window, activePlayerIndex, players[activePlayerIndex]->getPlayer().isBoostActive());


		//updating players

			players[0]->getPlayer().update(timeManager->getDeltaTime(), players[0]->getPlayer().getX(), obstaclesPtr->getObstacles(), window, vol);

			if (players[0]->getPlayer().didFallInPit()) {
				lvlLost = true;
				return;
			}
			window.draw(players[0]->getPlayer().getSprite());

		//updating enemies
			enemies[0]->getEnemy().update(timeManager->getDeltaTime(), enemies[0]->getEnemy().getEnemyX() - camera->getCameraPos() + 600.0f, window, players[activePlayerIndex]->getPlayer().getX(), players[activePlayerIndex]->getPlayer().getY(), gravity, vol, obstaclesPtr->getObstacles());
			//only checking for collision if player is not invincible
			if (!players[activePlayerIndex]->getPlayer().getInvincibilityStatus()) {
				//player enemy collision
				if (enemies[0]->getEnemy().getCD().checkEnemy(players[activePlayerIndex]->getPlayer().getCD(), players[activePlayerIndex]->getPlayer().getX(), players[activePlayerIndex]->getPlayer().getY(), enemies[0]->getEnemy().getEnemyX(), enemies[0]->getEnemy().getEnemyY())) {
					if (!players[0]->getPlayer().getIsRolling()) {
						teamHealth--;
						damageSound.play();
						players[0]->getPlayer().getInvincibilityClock().restart();
						players[0]->getPlayer().setInvincibility(true);
					}
					else {
						attackSound.play();
						enemies[0]->getEnemy().decHealth();
						if (enemies[0]->getEnemy().getHealth() <= 0)
							defeatedEnemies++;
					}
				}
				//player needle collision
			}
			window.draw(enemies[0]->getEnemy().getNeedleSprite());
			window.draw(enemies[0]->getEnemy().getSprite());
			

		//displaying everything 
		window.display();
	}
}

void BossLevel::switchActivePlayer()
{

}


void BossLevel::followActivePlayer(int i, RenderWindow& window)
{

}

//TODO
void BossLevel::flyWithTails(int i, RenderWindow& window)
{
	
}