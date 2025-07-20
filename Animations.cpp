#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animations.h"
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;


Animations::Animations()
{
	runSourceRightSonicTex.loadFromFile("Data\\0right.png");
	runSourceLeftSonicTex.loadFromFile("Data\\0left.png");
	runSourceRightSonic.setTexture(runSourceRightSonicTex);
	runSourceLeftSonic.setTexture(runSourceLeftSonicTex);
}


void Animations::initializeAnimations() {
	rightRect.left = 0;
	rightRect.top = 0;
	rightRect.width = 40;
	rightRect.height = 40;

		leftRect.left = 440;
		leftRect.top = 0;
		leftRect.width = 40;
		leftRect.height = 40;

		//ringRect.left = 0;
		//ringRect.top = 0;
		//ringRect.width = 16;
		//ringRect.height = 16;

		(runSourceRightSonic).setPosition(600.0f, 560.0f);
		(runSourceLeftSonic).setPosition(600.0f, 560.0f);
		(runSourceLeftSonic).setScale(2.5, 2.5);
		(runSourceRightSonic).setScale(2.5, 2.5);

		//ring->setPosition(200, 595);
	}
	void Animations::runRightSonic(RenderWindow& window, Sprite& playerSprite) {
		if (dt.getElapsedTime().asSeconds() > 1.0f/60.0f) {
			if (rightRect.left < 440) {
				rightRect.left += 40;
			}
			else {
				rightRect.left = 0;
			}
			playerSprite.setTexture(runSourceRightSonicTex);
			playerSprite.setTextureRect(rightRect);
			dt.restart();
		}

	}

	void Animations::runLeftSonic(RenderWindow& window, Sprite& playerSprite) {
		if (dt.getElapsedTime().asSeconds() > 1.0/60.0f) {
			if (leftRect.left > 0) {
				leftRect.left -= 40;
			}
			else {
				leftRect.left = 440;
			}
			playerSprite.setTexture(runSourceLeftSonicTex);
			playerSprite.setTextureRect(leftRect);
			dt.restart();
		}

	}



	/*void animateRing(RenderWindow& window, Clock& dt) {
		if (dt.getElapsedTime().asSeconds() > 1.0f) {
			if (ringRect.left <= 64) {
				ringRect.left += 16;
				(*ring).setTextureRect(ringRect);
			}
			else {
				ringRect.left = 0;
				(*ring).setTextureRect(ringRect);
			}
			dt.restart();
		}

		window.draw(*ring);
	}*/
