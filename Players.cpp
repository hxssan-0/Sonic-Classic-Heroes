#pragma once
#include <iostream>
#include <cmath>
#include "Players.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Players::Players(float maxVelocityX, float maxVelocityY, string texPath, float acc, float sclX, float sclY, float imX, float imY)
{
	scaleX = sclX;
	scaleY = sclY;
	imgX = imX;
	imgY = imY;
	playerX = 0.0f;
	playerY = 560.0f;
	offsetY = playerY;
	playerSprite.setPosition(playerX + 600.0f, playerY);
	this->maxVelocityX = maxVelocityX;
	terminalVelocity = maxVelocityY;
	velocityX = 0;
	velocityY = 0;
	playerTex.loadFromFile(texPath);
	playerSprite.setTexture(playerTex);
	playerSprite.setScale(scaleX, scaleY);
	isInvincible = false;
	invincibilityTime = 1.0f;
	acceleration = acc;
	isOnGround = true;
	playerWidth = imgX * scaleX;
	playerHeight = imgY * scaleY;
	hitboxX = 8 * scaleX;
	hitboxY = 5 * scaleY;
	jumpStrength = -22;
	moveLeft = moveDown = moveRight = moveUp = true;
	onSpike = quickJump = false;
	cd = nullptr;
	isFlying = false;
	isRolling = false;
	facingLeft = false;
	facingRight = true;
	fellInPit = false;
	boostActivated = false;
	jumpBuffer.loadFromFile("Sprites\\Sounds\\Global\\Jump.wav");
	jumpSound.setBuffer(jumpBuffer);
	drawSprite = true;
}

Sprite& Players::getSprite()
{
	return playerSprite;
}

void Players::setModifiers(float g, float f)
{
	gravity = g;
	friction = f;
	deceleration = acceleration * friction;
}

float Players::getX() const
{
	return playerX;
}

float Players::getY() const
{
	return playerY;
}

void Players::implementGravity(char** obstacles)
{
	offsetY = playerY;

	if (!isOnGround) {
		offsetY += velocityY;
	}

	char bottom_left_down = obstacles[(int)(offsetY + hitboxY + playerHeight) / 64][(int)(playerX + hitboxX) / 64];
	char bottom_right_down = obstacles[(int)(offsetY + hitboxY + playerHeight) / 64][(int)(playerX + playerWidth) / 64];
	char bottom_mid_down = obstacles[(int)(offsetY + hitboxY + playerHeight) / 64][(int)(playerX + playerWidth / 2) / 64];

	if (bottom_left_down == 's' || bottom_mid_down == 's' || bottom_right_down == 's') {
		onSpike = true;
	}
	else {
		onSpike = false;
	}


	if (bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' || bottom_left_down == 's' || bottom_mid_down == 's' || bottom_right_down == 's' || bottom_left_down == 'p' || bottom_mid_down == 'p' || bottom_right_down == 'p')
	{
		isOnGround = true;
	}
	else
	{
		bool dummy = false;
		cd->detectCollision(playerX, offsetY, moveRight, moveLeft, moveUp, moveDown, onSpike, quickJump, dummy);
		if (velocityY < 0 && !moveUp) {
			velocityY = 0;
		}
		playerY = offsetY;
		isOnGround = false;
	}

	if (!isOnGround)
	{
		velocityY += gravity;
		if (velocityY >= terminalVelocity) velocityY = terminalVelocity;
	}

	else
	{
		velocityY = 0;
	}

}

void Players::resetBooleans()
{
	moveLeft = true;
	moveRight = true;
	moveUp = true;
	moveDown = false;
}

void Players::createCollisionDetection(char** grid, char** collectibles)
{
	cd = new CollisionDetection(hitboxX, hitboxY + 32, playerHeight, playerWidth, 64, grid, collectibles);
}

void Players::setActive()
{
	isActive = true;
}

void Players::setInactive()
{
	isActive = false;
}

bool Players::isAirborne() const
{
	return isFlying;
}

void Players:: setFlying()
{
	isFlying = true;
}

void Players::setGrounded()
{
	isFlying = false;
}

CollisionDetection& Players::getCD() const
{
	return *cd;
}

bool Players::getInvincibilityStatus() const
{
	return isInvincible;
}

Clock& Players::getInvincibilityClock()
{
	return invincibilityClk;
}

float Players::getInvincibilityTime() const
{
	return invincibilityTime;
}

void Players::setInvincibility(bool b)
{
	isInvincible = b;
}

bool Players::getIsRolling() const
{
	return isRolling;
}

bool Players::getIsOnSpike() const
{
	return onSpike;
}

bool Players::didFallInPit() const
{
	return fellInPit;
}

void Players::setX(float x) {
	playerX = x;
}

void Players::setY(float y) {
	playerY = y;
}

bool Players::isBoostActive() const
{
	return boostActivated;
}

//TODO --- remaining functions

