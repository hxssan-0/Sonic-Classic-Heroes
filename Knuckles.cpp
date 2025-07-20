#pragma once
#include <iostream>
#include "Knuckles.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
//TODO --- change/adjust
Knuckles::Knuckles() : Players(600.0f, 640.0f, "Data\\knuckles_sprite.png", 900.0f, 2.5f, 2.5f, 24, 35) {
	isActive = false;
	rollSpeed = 600.0f; //adjust if needed
} //check raw img x/y

void Knuckles::update(float dt, float x, char** obstacles, RenderWindow& window, float vol)
{
	fellInPit = false;
	jumpSound.setVolume(vol);
	drawSprite = true;
	if (!isFlying)
		implementGravity(obstacles);
	if (invincibilityTime == 15 && invincibilityClk.getElapsedTime().asSeconds() > invincibilityTime) {
		isInvincible = false;
		invincibilityTime = 1;
	}
	bool pitFound = false;
	cd->detectCollision(playerX, playerY, moveRight, moveLeft, moveUp, moveDown, onSpike, quickJump, pitFound, isActive);
	if (pitFound) {
		fellInPit = true;
		return;
	}
	//to help with platforms
	if (quickJump) {
		playerY -= 50;
		quickJump = false;
	}
	if (onSpike && !isInvincible && isActive) {
		velocityY -= 20;
		isOnGround = false;
	}
	move(dt, window);
	if (Keyboard::isKeyPressed(Keyboard::Up) && isOnGround && moveUp && !isFlying) {
		jump(dt);
	}
	if (abs(velocityX) >= rollSpeed && !isFlying) {
		isRolling = true;
		/*playerSprite.setTextureRect(sf::IntRect(0, 0, sonicBallTex.getSize().x, sonicBallTex.getSize().y));
		playerSprite.setTexture(sonicBallTex);*/
	}
	else if (abs(velocityY) > 1 && !isOnGround && !isFlying) {
		//basically jumping
		isRolling = true;
	}
	else {
		isRolling = false;
	}
	if (velocityX == 0) {
		if ((isOnGround || isFlying) && facingRight && !isRolling) {
			playerSprite.setTextureRect(sf::IntRect(0, 0, playerTex.getSize().x, playerTex.getSize().y));
			playerSprite.setTexture(playerTex);
		}
		else if ((isOnGround || isFlying) && facingLeft && !isRolling) {
			/*playerSprite.setTextureRect(sf::IntRect(0, 0, sonicLeftTex.getSize().x, sonicLeftTex.getSize().y));
			playerSprite.setTexture(sonicLeftTex);*/
		}
	}

	if (!isFlying && !isOnGround && velocityY < 0) {
		/*playerSprite.setTextureRect(sf::IntRect(0, 0, sonicBallTex.getSize().x, sonicBallTex.getSize().y));
		playerSprite.setTexture(sonicBallTex);*/
	}

	if (isOnGround && velocityX != 0 && !isRolling) {
		drawSprite = false;
		if (facingRight) {
			/*animations->runRightSonic(window, playerSprite);*/
		}
		else if (facingLeft) {
			/*animations->runLeftSonic(window, playerSprite);*/
		}
	}
	resetBooleans();
	playerSprite.setPosition(x, playerY);
}


void Knuckles::jump(float dt)
{
	velocityY = jumpStrength;
}

void Knuckles::move(float dt, RenderWindow& window)
{
	if (Keyboard::isKeyPressed(Keyboard::Right) && moveRight) {
		/*animations->runRight(window);*/
		velocityX += acceleration * dt;
		if (velocityX > maxVelocityX)
			velocityX = maxVelocityX;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && moveLeft) {
		/*animations->runLeft(window);*/
		velocityX -= acceleration * dt;
		if (velocityX < -maxVelocityX)
			velocityX = -maxVelocityX;
	}
	else
	{
		if (velocityX < 0) {
			velocityX += deceleration * dt;
			if (velocityX > 0)
				velocityX = 0;
		}
		else if (velocityX > 0) {
			velocityX -= deceleration * dt;
			if (velocityX < 0)
				velocityX = 0;
		}
	}
	//horizontal collision detection done here to prevent skipping over an obstacles
	//this is done so that the collision is checked before updating the player position
	//by checking with the to be updated position first
	moveRight = moveLeft = true;
	float temp = playerX + velocityX * dt;
	if (velocityX > 0) {
		bool pitFound = false;
		cd->detectCollision(temp, playerY, moveRight, moveLeft, moveUp, moveDown, onSpike, quickJump, pitFound, isActive);
		if (pitFound) {
			fellInPit = true;
			return;
		}
		if (!moveRight)
			velocityX = 0;
	}
	else if (velocityX < 0) {
		bool pitFound = false;
		cd->detectCollision(temp, playerY, moveRight, moveLeft, moveUp, moveDown, onSpike, quickJump, pitFound, isActive);
		if (pitFound) {
			fellInPit = true;
			return;
		}
		if (!moveLeft)
			velocityX = 0;
	}
	playerX += velocityX * dt;
	if (playerX < 0)
		playerX = 0;

}

void Knuckles::moveToTarget(float targetX, float dt, float targetY)
{
	float maxSpeed = 900.0f;
	if (targetX < playerX) {
		playerX -= maxSpeed * dt;
	}
	else {
		playerX += maxSpeed * dt;
	}

	float followSpeedY = 300;
	if (isFlying) {
		if (playerY < targetY)
			playerY += followSpeedY * dt;
		else
			playerY -= followSpeedY * dt;
	}

}

void Knuckles::activateBoost()
{
	isInvincible = true;
	invincibilityTime = 15;
	invincibilityClk.restart();
}