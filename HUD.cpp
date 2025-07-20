#pragma once
#include <iostream>
#include "HUD.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

HUD::HUD()
{
	healthTex.loadFromFile("Sprites\\heart_sprite.png");
	healthSprite.setTexture(healthTex);
	ringTex.loadFromFile("Sprites\\ring_sprite.png");
	ringSprite.setTexture(ringTex);
	ringSprite.setScale(0.75f, 0.75f);
	ringSprite.setPosition(25, 90);
	healthSprite.setScale(0.75f, 0.75f);
	hudFont.loadFromFile("Fonts\\PressStart2P-Regular.ttf");
	timeText.setFont(hudFont);
	scoreText.setFont(hudFont);
	ringText.setFont(hudFont);
	invincibleText.setFont(hudFont);
	activeText.setFont(hudFont);
	boostText.setFont(hudFont);
	boostText.setCharacterSize(25);
	boostText.setFillColor(Color::Magenta);
	boostText.setPosition(950, 800);
	activeText.setCharacterSize(25);
	activeText.setPosition(25, 800);
	invincibleText.setString("Invincibility");
	invincibleText.setCharacterSize(25);
	invincibleText.setFillColor(Color::White);
	invincibleText.setPosition(25, 850);
	timeText.setFillColor(Color::Yellow);
	timeText.setCharacterSize(25);
	timeText.setPosition(30, 30);
	scoreText.setFillColor(Color::Yellow);
	scoreText.setCharacterSize(25);
	scoreText.setPosition(30, 60);
	ringText.setFillColor(Color::Yellow);
	ringText.setCharacterSize(25);
	ringText.setPosition(90, 97);
}

void HUD::updateHUD(int score, float timeElapsed, int health, int rings, bool isInvincible, float levelTime, RenderWindow& window, int activeIndex, bool boostActivated)
{
	int time = levelTime - timeElapsed;
	timeText.setString("Time:" + to_string(time));
	scoreText.setString("Score:" + to_string(score));
	ringText.setString(":" + to_string(rings));
	for (int i = 0; i < health; i++) {
		healthSprite.setPosition(25 + (i * 30), 140);
		window.draw(healthSprite);
	}

	if (activeIndex == 0) {
		activeText.setFillColor(Color::Blue);
		activeText.setString("Sonic is Active");
	}
	else if (activeIndex == 2) {
		activeText.setFillColor(Color::Red);
		activeText.setString("Knuckles is Active");
	}
	else if (activeIndex == 1) {
		activeText.setFillColor(Color::Yellow);
		activeText.setString("Tails is Active");
	}

	if (boostActivated) {
		if (activeIndex == 0)
			boostText.setString("+4 Speed");
		else if (activeIndex == 1)
			boostText.setString("+4s Flight");
	}

	window.draw(timeText);
	window.draw(scoreText);
	window.draw(ringSprite);
	window.draw(ringText);
	window.draw(activeText);
	if (isInvincible)
		window.draw(invincibleText);
	if (boostActivated && activeIndex != 2)
		window.draw(boostText);

}