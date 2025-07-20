#pragma once
#include <iostream>
#include "TimeManager.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class HUD
{
private:
	Texture healthTex;
	Sprite healthSprite;
	Texture ringTex;
	Sprite ringSprite;
	Font hudFont;
	Text timeText;
	Text ringText;
	Text scoreText;
	Text invincibleText;
	Text activeText;
	Text boostText;
public:
	HUD();

	void updateHUD(int score, float timeElapsed, int health, int rings, bool isInvincible, float levelTime, RenderWindow&, int activeIndex, bool boostActivated);

};