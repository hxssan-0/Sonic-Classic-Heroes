#pragma once
#include <iostream>
#include "EggStinger.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

//TODO --- adjust speeds, ranges and coordinates, also fix sprite
EggStinger::EggStinger(float eX, float eY) : Flyers(20, 150.0f, 100.0f, eX, eY, 1200.0f, 340.0f, 10.0f, false, "Sprites\\boss_sprite.png", 1.0f, 1.0f, 24, 35)
{
	spikeTex.loadFromFile("Sprites\\needle_sprite.png");
	spikeSprite.setTexture(spikeTex);
	spikeX = enemyX;
	spikeY = enemyY;
	eggWidth = 145;
	eggHeight = 130;
	eggSpikeWidth = 91;
	eggSpikeHeight = 88;
	attackP = false;
	mR = true;
	mL = false;
	moveToTarget = false;
	findTarget = false;
	reverse = false;
	original = false;
	delay = false;
	target_x = 0;
	target_y = 0;
	reverse_y = 100;
	spikeSprite.setPosition(((eggWidth - eggSpikeWidth) / 2), (eggHeight - eggSpikeHeight));
	char** dummy1 = nullptr;
	char** dummy2 = nullptr;
	cdSpike = new CollisionDetection(8 , 5, 88, 91, 64, dummy1, dummy2);
}

void EggStinger::update(float dt, float x, RenderWindow& window, float targetX, float targetY, float gravity, float vol, char** lvl)
{
	if (dtt.getElapsedTime().asSeconds() < 0.5f && !attackP && !reverse) {
		moveBoss(enemyX, enemyY, enemySprite, mL, mR);
		spikeX = ((eggWidth - eggSpikeWidth) / 2) + enemyX - 10;
		spikeY = (eggHeight - eggSpikeHeight) + enemyY;
		spikeSprite.setPosition(spikeX, spikeY);
	}
	else if (!attackP && !reverse) {
		dtt.restart();
	}

	if (attack.getElapsedTime().asSeconds() >= 10 && !attackP && !reverse) {
		attackP = true;
		findTarget = true;
		dtt.restart();
	}


	if (attackP && findTarget && !reverse) {
		findPlayer(targetX, targetY, target_x, target_y, height, lvl);
		findTarget = false;
		moveToTarget = true;

	}

	if (dtt.getElapsedTime().asSeconds() < 0.5f && attackP && moveToTarget && !reverse) {
		moveBoss(enemyX, enemyY, target_x, enemySprite, moveToTarget);
		spikeX = ((eggWidth - eggSpikeWidth) / 2) + enemyX - 10;
		spikeY = (eggHeight - eggSpikeHeight) + enemyY;
		spikeSprite.setPosition(spikeX, spikeY);
	}
	else {
		dtt.restart();
	}

	if (dtt.getElapsedTime().asSeconds() < 0.5 && attackP && !moveToTarget && !reverse) {

		if (target_y != 0) {
			attackPlayer(enemyX, enemyY, spikeX, spikeY, target_y, target_x, spikeSprite, enemySprite, eggSpikeHeight, lvl, reverse, delay);
			spikeOut(enemyX, enemyY, spikeX, spikeY, eggHeight, eggSpikeHeight, spikeSprite);
		}
		else {
			attackP = false;
			moveToTarget = false;
			findTarget = false;
			reverse = false;
			original = false;
			delay = false;
		}

	}
	else {
		dtt.restart();
	}

	if (delay) {
		delayClock.restart();
		while (delayClock.getElapsedTime().asSeconds() < 2) {
			enemySprite.setPosition(enemyX, enemyY);
			spikeSprite.setPosition(spikeX, spikeY);
		}
		delay = false;
	}

	if (dtt.getElapsedTime().asSeconds() < 0.5f && attackP && !moveToTarget && reverse) {
		reverseBoss(enemyX, enemyY, reverse_y, enemySprite, reverse, attackP, moveToTarget, findTarget, original);
		spikeIn(enemyX, enemyY, spikeX, spikeY, eggHeight, eggSpikeHeight, spikeSprite);

	}

	else {
		dtt.restart();
	}

	if (original) {
		attack.restart();
		original = false;
	}
}

void EggStinger::moveBoss(float& boss_x, float& boss_y, Sprite& bossSprite, bool& mL, bool& mR) {
	if (boss_x < 1200 - 145 && mR) {
		boss_x += 2;
		bossSprite.setPosition(boss_x, boss_y);
	}
	else if (boss_x > 1200 - 145) {
		mL = true;
		mR = false;
	}

	if (boss_x > 0 && mL) {
		boss_x -= 2;
		bossSprite.setPosition(boss_x, boss_y);
	}
	else if (boss_x <= 0) {
		mL = false;
		mR = true;
	}
}

void EggStinger::moveBoss(float& boss_x, float& boss_y, int target_x, Sprite& bossSprite, bool& moveToTarget) {
	if (boss_x == target_x) {
		moveToTarget = false;
	}
	else if (boss_x > target_x) {
		boss_x -= 2;
		bossSprite.setPosition(boss_x, boss_y);
	}
	else if (boss_x < target_x) {
		boss_x += 2;
		bossSprite.setPosition(boss_x, boss_y);
	}
}

void EggStinger::findPlayer(float player_x, float player_y, int& target_x, int& target_y, int gridHeight, char** lvl) {
	target_x = player_x;
	for (int i = 0; i < gridHeight; i++) {
		if (lvl[i][(target_x / 64)] == 'w') {
			target_y = i * 64;
			return;
		}
	}
	target_y = 0;
}

void EggStinger::spikeOut(float boss_x, float boss_y, int& spike_x, int& spike_y, int bossHeight, int spikeHeight, Sprite& spike) {
	if (boss_y + spike_y < bossHeight + spikeHeight + boss_y - 2) {
		spike_y += 2;
	}
	spike.setPosition(spike_x, spike_y);
}

void EggStinger::attackPlayer(float& boss_x, float& boss_y, int& spike_x, int& spike_y, int& target_y, int& target_x, Sprite& spike, Sprite& boss, int spikeHeight, char** lvl, bool& reverse, bool& delay) {
	if (spike_y + spikeHeight < target_y) {
		boss_y += 1;
		spike_y += 1;
	}
	boss.setPosition(boss_x, boss_y);
	if (spike_y + spikeHeight == target_y) {
		lvl[(target_y / 64)][((target_x) / 64) + 1] = '\0';
		reverse = true;
		delay = true;
		target_y = 0;
	}
}

void EggStinger::reverseBoss(float& boss_x, float& boss_y, int reverse_y, Sprite& boss, bool& reverse, bool& attack, bool& moveToTarget, bool& findTarget, bool& original) {
	if (boss_y > reverse_y) {
		boss_y -= 1;
	}
	else if (boss_y == reverse_y) {
		reverse = false;
		moveToTarget = false;
		findTarget = false;
		attack = false;
		original = true;
	}
	boss.setPosition(boss_x, boss_y);
}

void EggStinger::spikeIn(float& boss_x, float& boss_y, int& spike_x, int& spike_y, int bossHeight, int spikeHeight, Sprite& spike) {
	if (spike_y > (bossHeight - spikeHeight) + boss_y) {
		spike_y -= 2;
	}

	spike.setPosition(spike_x, spike_y);
}

void EggStinger::moveEnemy(float dt, float targetX, float targetY)
{

}

Sprite& EggStinger::getNeedleSprite()
{
	return spikeSprite;
}