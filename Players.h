#pragma once
#include <iostream>
#include "CollisionDetection.h"
#include "Animations.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Players
{
protected:
	float playerX, playerY; //default parameters, start at the center of the screen
	float offsetY;
	float velocityX, velocityY; //default
	float maxVelocityX, terminalVelocity;
	Texture playerTex;
	Sprite playerSprite;
	Texture playerTexLeft;
	Sprite playerSpriteLeft;
	bool isInvincible; //default
	float invincibilityTime; //default
	Clock invincibilityClk;
	float jumpStrength;
	float acceleration;
	float deceleration;
	bool isOnGround; //default
	float gravity;
	float friction;
	float scaleX, scaleY;
	int imgX, imgY;
	float playerWidth, playerHeight;
	float hitboxX, hitboxY;
	bool markerCrossed;
	Animations* animations;
	bool moveLeft, moveRight, moveUp, moveDown, onSpike, quickJump;
	CollisionDetection* cd;
	bool isActive;
	bool isFlying;
	Clock flyClk;
	bool isRolling;
	float rollSpeed;
	bool facingLeft, facingRight;
	bool fellInPit;
	bool boostActivated;
	bool drawSprite;
	SoundBuffer jumpBuffer;
	Sound jumpSound;

public:
	Players(float maxVelocityX, float maxVelocityY, string texPath, float acc, float sclX, float sclY, float imX, float imY);

	virtual void update(float dt, float x, char** obstacles, RenderWindow&, float vol) = 0;

	virtual void moveToTarget(float targetX, float dt, float targetY) = 0;

	virtual void jump(float dt) = 0;

	virtual void move(float dt, RenderWindow&) = 0;

	virtual void createCollisionDetection(char** grid, char** collectibles);

	Sprite& getSprite();

	void setModifiers(float g, float f);

	void implementGravity(char** obstacles);

	virtual void resetBooleans();

	float getX() const;

	float getY() const;

	void setX(float x);

	void setY(float y);

	virtual void activateBoost() = 0;

	void setActive();

	void setInactive();

	bool isAirborne() const;

	void setFlying();

	void setGrounded();

	bool getIsRolling() const;

	bool getInvincibilityStatus() const;

	bool getIsOnSpike() const;

	bool didFallInPit() const;

	bool isBoostActive() const;

	Clock& getInvincibilityClock();

	float getInvincibilityTime() const;

	void setInvincibility(bool b);

	CollisionDetection& getCD() const;
};