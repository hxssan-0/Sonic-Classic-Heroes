#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Level3.h"
using namespace std;
using namespace sf;

//TODO
Level3::Level3(int& vol, int highscore) : Levels(16, 300, 14, 0.5f, 0.95f, "", highscore, vol) {
	lvlBgTex = new Texture[numBgSprites];
	lvlBgSprites = new Sprite[numBgSprites];
	players = new PlayerFactory * [3];
	players[0] = new SonicFactory;
	players[1] = new TailsFactory;
	players[2] = new KnucklesFactory;
	for (int i = 0; i < 3; i++)
		players[i]->createPlayer();
	for (int i = 0; i < 3; i++) {
		players[i]->getPlayer().setModifiers(gravity, friction);
	}
	//adjust according to number and types of enemies
	numEnemies = 8; //adjust
	enemies = new EnemyFactory * [numEnemies];
	levelTime = 180.0f; //3 mins for this level
	numRings = 25; //adjust
	numLives = 3; //adjust
	numBoosts = 2; //adjust
	teamHealth = 7;

}

//TODO
Level3::~Level3() {}

//TODO
void Level3::createBackground() {
	lvlBgTex[0].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[1].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[2].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[3].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[4].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[5].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[6].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[7].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[8].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[9].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[10].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[11].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[12].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[13].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[14].loadFromFile("Backgrounds\\lvl3_bg.jpg");
	lvlBgTex[15].loadFromFile("Backgrounds\\lvl3_bg.jpg");
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

void Level3::createObstacles()
{
	wallTex1.loadFromFile("Sprites\\moon_block_sprite.png");
	wallSprite1.setTexture(wallTex1);
	platformTex.loadFromFile("Data\\brick2.png");
	platformSprite.setTexture(platformTex);
	spikeTex.loadFromFile("Data\\spike.png");
	spikeSprite.setTexture(spikeTex);
	breakableWallTex.loadFromFile("Sprites\\breakable_wall_sprite.png");
	breakableWallSprite.setTexture(breakableWallTex);
	//ground
	for (int j = 0; j < 300; j++) {
		obstaclesPtr->createObstacle(0, j, 'w');
	}
	for (int j = 0; j < 300; j++) {
		if (j == 26 || j == 29 || (j >= 46 && j < 74)) {
			obstaclesPtr->createObstacle(12, j, 'h');
			continue;
		}
		obstaclesPtr->createObstacle(11, j, 'w');
	}

	for (int j = 12; j < 20; j++) {
		obstaclesPtr->createObstacle(8, j, 'w');
	}

	for (int j = 15; j < 18; j++) {
		obstaclesPtr->createObstacle(5, j, 'w');
	}

	obstaclesPtr->createObstacle(10, 31, 's');
	obstaclesPtr->createObstacle(10, 38, 's');


	for (int i = 10; i > 7; i--) {
		obstaclesPtr->createObstacle(i, 42, 'b');
		obstaclesPtr->createObstacle(i, 43, 'b');
		obstaclesPtr->createObstacle(i, 45, 'b');
		obstaclesPtr->createObstacle(i, 46, 'w');
	}

	for (int j = 7; j > 0; j--)
		obstaclesPtr->createObstacle(j, 45, 'b');

	for (int j = 42; j < 45; j++)
		obstaclesPtr->createObstacle(7, j, 'w');

	for (int j = 46; j < 74; j++) {
		obstaclesPtr->createObstacle(10, j, 'h');
	}

	for (int j = 75; j < 100; j++) {
		for (int i = 10; i > 4; i--) {
			obstaclesPtr->createObstacle(i, j, 'w');
		}
	}
	obstaclesPtr->createObstacle(4, 78, 's');
	obstaclesPtr->createObstacle(4, 78, 's');

	for (int i = 4; i > 0; i--) {
		obstaclesPtr->createObstacle(i, 99, 'w');
	}

	for (int i = 10; i > 4; i--) {
		obstaclesPtr->createObstacle(i, 93, 'e');
		obstaclesPtr->createObstacle(i, 94, 'e');
	}

	for (int i = 95; i < 100; i++) {
		obstaclesPtr->createObstacle(10, i, 'e');
		obstaclesPtr->createObstacle(9, i, 'e');
		obstaclesPtr->createObstacle(8, i, 'e');
	}

	for (int i = 100; i < 200; i++) {
		obstaclesPtr->createObstacle(4, i, 'w');
	}

	for (int i = 120; i < 180; i += 4) {
		obstaclesPtr->createObstacle(10, i, 's');
	}

	for (int i = 10; i > 4; i--) {
		obstaclesPtr->createObstacle(i, 200, 'b');
	}


	for (int i = 0; i < 3; i++) {
		players[i]->getPlayer().createCollisionDetection(obstaclesPtr->getObstacles(), collectibles);
	}
}

void Level3::createCollectibles()
{

	for (int j = 32; j < 38; j++) {
		collectiblesFactories[0]->createCollectible(10, j);
		collectibles[10][j] = 'r';
	}

	collectiblesFactories[2]->createCollectible(4, 16);
	collectibles[4][16] = 'b';

	collectiblesFactories[1]->createCollectible(10, 44);
	collectibles[10][44] = 'h';
	collectiblesFactories[1]->createCollectible(10, 162);
	collectibles[10][162] = 'h';

	for (int j = 80; j < 89; j++) {
		collectiblesFactories[0]->createCollectible(4, j);
		collectibles[4][j] = 'r';
	}

	collectiblesFactories[2]->createCollectible(10, 150);
	collectibles[10][150] = 'b';

	for (int j = 190; j < 200; j++) {
		collectiblesFactories[0]->createCollectible(10, j);
		collectibles[10][j] = 'r';
	}

}

void Level3::createEnemies()
{
	enemies[0] = new CrabMeatFactory;
	enemies[0]->createEnemy(300.0f, 600.0f);
	enemies[1] = new BeeBotFactory;
	enemies[1]->createEnemy(1200.0f, 400.0f);
	enemies[2] = new MotoBugFactory;
	enemies[2]->createEnemy(2400.0f, 600.0f);
	enemies[3] = new BatBrainFactory;
	enemies[3]->createEnemy(5888.0f, 128.0f);
	enemies[4] = new CrabMeatFactory;
	enemies[4]->createEnemy(10240.0f, 600.0f);
	enemies[5] = new BeeBotFactory;
	enemies[5]->createEnemy(10500.0f, 400.0f);
	enemies[6] = new BatBrainFactory;
	enemies[6]->createEnemy(11520.0f, 300.0f);
	enemies[7] = new CrabMeatFactory;
	enemies[7]->createEnemy(14000.0f, 600.0f);
}

void Level3::drawCollectibles(RenderWindow& window)
{
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 300; j++) {
			if (collectibles[i][j] == 'r') {
				collectiblesFactories[0]->getCollectible().getSprite().setPosition(j * cellSize - camera->getCameraPos() + 600.0f, i * cellSize);
				window.draw(collectiblesFactories[0]->getCollectible().getSprite());
			}
			else if (collectibles[i][j] == 'h') {
				collectiblesFactories[1]->getCollectible().getSprite().setPosition(j * cellSize - camera->getCameraPos() + 600.0f, i * cellSize);
				window.draw(collectiblesFactories[1]->getCollectible().getSprite());
			}
			else if (collectibles[i][j] == 'b') {
				collectiblesFactories[2]->getCollectible().getSprite().setPosition(j * cellSize - camera->getCameraPos() + 600.0f, i * cellSize);
				window.draw(collectiblesFactories[2]->getCollectible().getSprite());
			}
		}
	}
}

void Level3::drawObstacles(RenderWindow& window)
{
	for (int i = 0; i < 14; i += 1)
	{
		for (int j = 0; j < 300; j += 1)
		{
			if (obstaclesPtr->checkObstacle(i, j, 'w'))
			{
				wallSprite1.setPosition(j * cellSize - camera->getCameraPos() + 600.0f, i * cellSize);
				window.draw(wallSprite1);
			}
			else if (obstaclesPtr->checkObstacle(i, j, 'p')) {
				platformSprite.setPosition(j * cellSize - camera->getCameraPos() + 600.0f, i * cellSize);
				window.draw(platformSprite);
			}
			else if (obstaclesPtr->checkObstacle(i, j, 's')) {
				spikeSprite.setPosition(j * cellSize - camera->getCameraPos() + 600.0f, i * cellSize);
				window.draw(spikeSprite);
			}
			else if (obstaclesPtr->checkObstacle(i, j, 'b')) {
				breakableWallSprite.setPosition(j * cellSize - camera->getCameraPos() + 600.0f, i * cellSize);
				window.draw(breakableWallSprite);
			}
		}
	}
}

//TODO
bool Level3::isLevelLost()
{
	if (timeManager->getTotalTime() > levelTime || teamHealth <= 0 || players[activePlayerIndex]->getPlayer().didFallInPit()) {
		lvlLost = true;
		return true;
	}
	lvlLost = false;
	return false;
}

//TODO
bool Level3::isLevelWon() {
	if ((defeatedEnemies == numEnemies) && (collectedRings == numRings) && (players[activePlayerIndex]->getPlayer().getX() > lvlWidth - 600.0f)) {
		lvlWon = true;
		return true;
	}
	lvlWon = false;
	return false;
}

void Level3::runLevel(RenderWindow& window) {

	if (!levelInit) {
		createBackground();
		createCollectibles();
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

		//camera update
		camera->runCamera(window, players[activePlayerIndex]->getPlayer().getX(), cellsX);

		//drawing obstacles
		drawObstacles(window);

		//drawing collectibles
		drawCollectibles(window);

		//calculating the score
		lvlScore = (defeatedEnemies * 200) + (collectedRings * 50);
		int tempScore = highscore + lvlScore;

		//displaying hud
		hud->updateHUD(tempScore, timeManager->getTotalTime(), teamHealth, collectedRings, players[activePlayerIndex]->getPlayer().getInvincibilityStatus(), levelTime, window, activePlayerIndex, players[activePlayerIndex]->getPlayer().isBoostActive());


		//updating players
		for (int i = 0; i < 3; i++) {
			float x = camera->worldToWindow(players[i]->getPlayer().getX());

			players[i]->getPlayer().update(timeManager->getDeltaTime(), x, obstaclesPtr->getObstacles(), window, vol);

			if (!playerActivity[i]) {
				if (players[i]->getPlayer().didFallInPit()) {
					players[i]->getPlayer().setX(players[activePlayerIndex]->getPlayer().getX());
					players[i]->getPlayer().setY(players[activePlayerIndex]->getPlayer().getY());
				}
			}

			if (!playerActivity[i])
				followActivePlayer(i, window);

			if (activePlayerIndex == 1 && players[1]->getPlayer().isAirborne()) {
				flyWithTails(i, window);
			}
			else {
				players[i]->getPlayer().setGrounded();
			}
			if (i == activePlayerIndex) {
				bool boostFound = false;
				players[i]->getPlayer().getCD().checkItem(players[i]->getPlayer().getX(), players[i]->getPlayer().getY(), collectedRings, teamHealth, vol, boostFound);
				if (boostFound) {
					players[i]->getPlayer().activateBoost();
				}
				if (players[i]->getPlayer().getIsOnSpike() && !players[i]->getPlayer().getInvincibilityStatus()) {
					teamHealth--;
					damageSound.play();
					players[i]->getPlayer().getInvincibilityClock().restart();
					players[i]->getPlayer().setInvincibility(true);
				}
				//resetting invincibility
				if (players[i]->getPlayer().getInvincibilityStatus()) {
					if (players[i]->getPlayer().getInvincibilityClock().getElapsedTime().asSeconds() > players[i]->getPlayer().getInvincibilityTime()) {
						players[i]->getPlayer().setInvincibility(false);
					}
				}
			}
			window.draw(players[i]->getPlayer().getSprite());
		}

		//updating enemies
		for (int i = 0; i < numEnemies; i++) {
			if (!enemies[i]->getEnemy().getEnemyActivity())
				continue;
			enemies[i]->getEnemy().update(timeManager->getDeltaTime(), enemies[i]->getEnemy().getEnemyX() - camera->getCameraPos() + 600.0f, window, players[activePlayerIndex]->getPlayer().getX(), players[activePlayerIndex]->getPlayer().getY(), gravity, vol);
			//only checking for collision if player is not invincible
			if (!players[activePlayerIndex]->getPlayer().getInvincibilityStatus()) {
				//player enemy collision
				if (enemies[i]->getEnemy().getCD().checkEnemy(players[activePlayerIndex]->getPlayer().getCD(), players[activePlayerIndex]->getPlayer().getX(), players[activePlayerIndex]->getPlayer().getY(), enemies[i]->getEnemy().getEnemyX(), enemies[i]->getEnemy().getEnemyY())) {
					if (!players[activePlayerIndex]->getPlayer().getIsRolling()) {
						teamHealth--;
						damageSound.play();
						players[activePlayerIndex]->getPlayer().getInvincibilityClock().restart();
						players[activePlayerIndex]->getPlayer().setInvincibility(true);
					}
					else {
						attackSound.play();
						enemies[i]->getEnemy().decHealth();
						enemies[i]->getEnemy().setEnemyActivity(false);
						defeatedEnemies++;
					}
				}
				//player projectile collision
				if (enemies[i]->getEnemy().doesShootProjectiles()) {
					if (enemies[i]->getEnemy().getCD().checkEnemy(players[activePlayerIndex]->getPlayer().getCD(), players[activePlayerIndex]->getPlayer().getX(), players[activePlayerIndex]->getPlayer().getY(), enemies[i]->getEnemy().getProjectileX(), enemies[i]->getEnemy().getProjectileY())) {
						teamHealth--;
						damageSound.play();
						players[activePlayerIndex]->getPlayer().getInvincibilityClock().restart();
						players[activePlayerIndex]->getPlayer().setInvincibility(true);
					}
				}
			}
			enemies[i]->getEnemy().getProjectileSprite().setPosition(enemies[i]->getEnemy().getProjectileX() - camera->getCameraPos() + 600.0f, enemies[i]->getEnemy().getProjectileY());
			window.draw(enemies[i]->getEnemy().getSprite());
			window.draw(enemies[i]->getEnemy().getProjectileSprite());
		}

		//displaying everything 
		window.display();
	}
}

void Level3::switchActivePlayer()
{
	activePlayerIndex = (activePlayerIndex + 1) % 3;
	for (int i = 0; i < 3; i++) {
		if (i == activePlayerIndex) {
			playerActivity[i] = true;
			players[i]->getPlayer().setActive();
		}
		else {
			playerActivity[i] = false;
			players[i]->getPlayer().setInactive();
		}
	}
}


void Level3::followActivePlayer(int i, RenderWindow& window)
{

	float activeX = players[activePlayerIndex]->getPlayer().getX();
	float minDistance = 100.0f;
	float x = camera->getCameraPos();
	if (abs(players[i]->getPlayer().getX() - activeX) > minDistance) {
		players[i]->getPlayer().moveToTarget(activeX, timeManager->getDeltaTime(), x);
	}
}

//TODO
void Level3::flyWithTails(int i, RenderWindow& window)
{
	if (i == 1)
		return;
	players[i]->getPlayer().setFlying();
	float activeX = players[activePlayerIndex]->getPlayer().getX();
	float activeY = players[activePlayerIndex]->getPlayer().getY();
	float minDistance = 10.0f;
	if (abs(players[i]->getPlayer().getY() - activeY) > minDistance)
		players[i]->getPlayer().moveToTarget(activeX, timeManager->getDeltaTime(), activeY);
}