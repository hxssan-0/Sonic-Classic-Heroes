#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Level1.h"
using namespace std;
using namespace sf;

//TODO
Level1::Level1(int& vol, int highscore) : Levels(11, 200, 14, 1.0f, 0.95f, "", highscore, vol) {
	lvlBgTex = new Texture[numBgSprites];
	lvlBgSprites = new Sprite[numBgSprites]; 
	players = new PlayerFactory*[3];
	players[0] = new SonicFactory;
	players[1] = new TailsFactory;
	players[2] = new KnucklesFactory;
	for (int i = 0; i < 3; i++)
		players[i]->createPlayer();
	for (int i = 0; i < 3; i++) {
		players[i]->getPlayer().setModifiers(gravity, friction);
	}
	//adjust according to number and types of enemies
	numEnemies = 9; //adjust
	enemies = new EnemyFactory * [numEnemies];
	levelTime = 300.0f; //5 mins for this level
	numRings = 24; //adjust
	numLives = 2; //adjust
	numBoosts = 1; //adjust

}

//TODO
Level1::~Level1() {}

//TODO
void Level1::createBackground() {
	lvlBgTex[0].loadFromFile("Backgrounds\\labyrinth_bg.png");
	lvlBgTex[1].loadFromFile("Backgrounds\\labyrinth_bg.png");
	lvlBgTex[2].loadFromFile("Backgrounds\\labyrinth_bg.png");
	lvlBgTex[3].loadFromFile("Backgrounds\\labyrinth_bg.png");
	lvlBgTex[4].loadFromFile("Backgrounds\\labyrinth_bg.png");
	lvlBgTex[5].loadFromFile("Backgrounds\\labyrinth_bg.png");
	lvlBgTex[6].loadFromFile("Backgrounds\\labyrinth_bg.png");
	lvlBgTex[7].loadFromFile("Backgrounds\\labyrinth_bg.png");
	lvlBgTex[8].loadFromFile("Backgrounds\\labyrinth_bg.png");
	lvlBgTex[9].loadFromFile("Backgrounds\\labyrinth_bg.png");
	lvlBgTex[10].loadFromFile("Backgrounds\\labyrinth_bg.png");
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

void Level1::createObstacles()
{
	wallTex1.loadFromFile("Data\\brick1.png");
	wallSprite1.setTexture(wallTex1);
	platformTex.loadFromFile("Data\\brick2.png");
	platformSprite.setTexture(platformTex);
	spikeTex.loadFromFile("Data\\spike.png");
	spikeSprite.setTexture(spikeTex);
	breakableWallTex.loadFromFile("Sprites\\breakable_wall_sprite.png");
	breakableWallSprite.setTexture(breakableWallTex);
	//ground
	for (int j = 0; j < 200; j++) {
		obstaclesPtr->createObstacle(0, j, 'w');
	}
	for (int j = 0; j < 200; j++) {
		if (j == 12 || j == 13 || (j >= 43 && j <= 60)) {
			if (j >= 43 && j <= 60) {
				obstaclesPtr->createObstacle(12, j, 'h');
			}
			else {
				obstaclesPtr->createObstacle(12, j, 'h');
			}
			continue;
		}
		obstaclesPtr->createObstacle(11, j, 'w');
	}
	//first platform with rings on it
	for (int j = 14; j < 20; j++)
		obstaclesPtr->createObstacle(8, j, 'w');

	//big block of walls starting from 22
	for (int j = 22; j < 43; j++) {
		for (int i = 10; i > 4; i--)
		obstaclesPtr->createObstacle(i, j, 'w');
	}

	//in between this previous section, breakable wall, and before that a health (at 32)
	for (int i = 34; i < 37; i++) {
		for (int j = 4; j > 1; j--) {
			obstaclesPtr->createObstacle(j, i, 'b');
		}
	}

	//pits after that section

	//start with platforms that go up hiding a boost
	for (int i = 65; i < 70; i++) {
		obstaclesPtr->createObstacle(8, i, 'p');
	}

	for (int i = 70; i < 78; i++) {
		obstaclesPtr->createObstacle(5, i, 'w');
	}

	//bee bot a bit after

	//spikes in the next section
	for (int i = 80; i < 83; i++)
		obstaclesPtr->createObstacle(10, i, 's');

	//L shaped trap
	for (int i = 11; i > 8; i--)
		obstaclesPtr->createObstacle(i, 91, 'w');

	for (int i = 87; i < 92; i++) {
		obstaclesPtr->createObstacle(8, i, 'p');
	}

	for (int i = 8; i > 0; i--) {
		obstaclesPtr->createObstacle(i, 87, 'w');
	}

	//platform going up to ground with traps and enemies and rings
	for (int i = 105; i < 110; i++) {
		obstaclesPtr->createObstacle(8, i, 'w');
	}
	for (int i = 112; i < 142; i++) {
		obstaclesPtr->createObstacle(6, i, 'w');
	}
	for (int j = 11; j > 6; j--) {
		obstaclesPtr->createObstacle(j, 141, 'w');
	}
	for (int j = 5; j > 0; j--) {
		obstaclesPtr->createObstacle(j, 141, 'b');
	}

	obstaclesPtr->createObstacle(5, 120, 's');
	obstaclesPtr->createObstacle(5, 125, 's');

	for (int i = 10; i > 7; i--)
		obstaclesPtr->createObstacle(i, 170, 'w');

	for (int i = 4; i > 0; i--)
		obstaclesPtr->createObstacle(i, 170, 'w');
	

	for (int i = 0; i < 3; i++) {
		players[i]->getPlayer().createCollisionDetection(obstaclesPtr->getObstacles(), collectibles);
	}
}

void Level1::createCollectibles()
{

	for (int j = 14; j < 20; j++) {
		collectiblesFactories[0]->createCollectible(7, j);
		collectibles[7][j] = 'r';
	}

	collectiblesFactories[1]->createCollectible(4, 16);
	collectibles[4][32] = 'h';

	//rings after breakable wall
	for (int i = 37; i < 40; i++) {
		collectiblesFactories[0]->createCollectible(4, i);
		collectibles[4][i] = 'r';
	}

	//boost
	collectiblesFactories[2]->createCollectible(4, 73);
	collectibles[4][73] = 'b';

	collectiblesFactories[0]->createCollectible(7, 100);
	collectibles[7][100] = 'h';

	for (int j = 135; j < 141; j++) {
		collectiblesFactories[0]->createCollectible(10, j);
		collectibles[10][j] = 'r';
	}

	for (int i = 121; i < 125; i++) {
		collectiblesFactories[0]->createCollectible(5, i);
		collectibles[5][i] = 'r';
	}

	for (int i = 145; i < 150; i++) {
		collectiblesFactories[0]->createCollectible(7, i);
		collectibles[7][i] = 'r';
	}


}

void Level1::createEnemies()
{
	// 0 crabmeat, 2 beebot, 3 motobug, 1 batbrain
	enemies[0] = new CrabMeatFactory;
	enemies[0]->createEnemy(1856.0f, 256.0f);
	enemies[1] = new BatBrainFactory;
	enemies[1]->createEnemy(300.0f , 768.0f);
	enemies[2] = new BeeBotFactory;
	enemies[2]->createEnemy(4800.0f, 400.0f);
	enemies[3] = new MotoBugFactory;
	enemies[3]->createEnemy(7040.0f, 600.0f);
	enemies[4] = new CrabMeatFactory;
	enemies[4]->createEnemy(8448.0f, 600.0f);
	enemies[5] = new BeeBotFactory;
	enemies[5]->createEnemy(8192.0f, 200.0f);
	enemies[6] = new CrabMeatFactory;
	enemies[6]->createEnemy(9600.0f, 600.0f);
	enemies[7] = new BatBrainFactory;
	enemies[7]->createEnemy(9800.0f, 600.0f);
	enemies[8] = new MotoBugFactory;
	enemies[8]->createEnemy(10500.0f, 600.0f);
}

void Level1::drawCollectibles(RenderWindow& window)
{
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 200; j++) {
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

void Level1::drawObstacles(RenderWindow& window)
{
	for (int i = 0; i < 14; i += 1)
	{
		for (int j = 0; j < 200; j += 1)
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
bool Level1::isLevelLost()
{
	if (timeManager->getTotalTime() > levelTime || teamHealth <= 0 || players[activePlayerIndex]->getPlayer().didFallInPit()) {
		lvlLost = true;
		return true;
	}
	lvlLost = false;
	return false;
}

//TODO
bool Level1::isLevelWon() { 
	if ((defeatedEnemies == numEnemies) && (collectedRings == numRings) && (players[activePlayerIndex]->getPlayer().getX() > lvlWidth - 600.0f)) {
		lvlWon = true;
		return true;
	}
	lvlWon = false;
	return false;
}

void Level1::runLevel(RenderWindow& window) {

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

void Level1::switchActivePlayer()
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


void Level1::followActivePlayer(int i, RenderWindow& window)
{

	float activeX = players[activePlayerIndex]->getPlayer().getX();
	float minDistance = 100.0f;
	float x = camera->getCameraPos();
	if (abs(players[i]->getPlayer().getX() - activeX) > minDistance) {
		players[i]->getPlayer().moveToTarget(activeX, timeManager->getDeltaTime(), x);
	}
}

//TODO
void Level1::flyWithTails(int i, RenderWindow& window)
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