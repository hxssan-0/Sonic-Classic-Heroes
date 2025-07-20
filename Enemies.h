#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "CollisionDetection.h"
using namespace std;
using namespace sf;

class Enemies
{
protected:
	// Animations* animations;
	int health;
	float speedX;
	float speedY;
	float enemyX;
	float enemyY;
	float height;
	float width;
	float displacementX;
	float displacementY;
	float dX;
	float dY;
	float scaleX, scaleY;
	float enemyWidth, enemyHeight;
	float projectileX;
	float projectileY;
	Texture enemyTex;
	Sprite enemySprite;
	Texture projectileTex;
	Sprite projectileSprite;
	float attackCooldown;
	bool projectileActive;
	bool shootsProjectiles;
	bool enemyActive;
	CollisionDetection* cd;

public:
	Enemies(int hp, float sX, float sY, float eX, float eY, float disX, float disY, float cooldown, bool shoots, string enemyTexPath, float sclX, float sclY, float imgX, float imgY);

	virtual void update(float dt, float x, RenderWindow& window, float targetX = 0, float targetY = 0, float gravity = 0, float vol = 0, char** lvl = nullptr) = 0;

	void decHealth();

	float getAttackCooldown() const;

	float getEnemyX() const;

	float getEnemyY() const;

	float getProjectileX() const;

	float getProjectileY() const;

	bool getProjectileStatus() const;

	virtual Sprite& getNeedleSprite();

	int getHealth() const;

	bool doesShootProjectiles() const;

	float getEnemyWidth() const;

	float getEnemyHeight() const;

	bool getEnemyActivity() const;

	void setEnemyActivity(bool b);

	Sprite& getSprite();

	CollisionDetection& getCD();

	/*virtual void shootProjectile(float dt) = 0; give this only to those enemies which shoot*/ 

	virtual void moveEnemy(float dt, float targetX = 0, float targetY = 0) = 0; //the second argument is default to accomodate those enemies which follow the player

	//virtual void attackGround() = 0; give this only to the egg stinger boss

	Sprite& getProjectileSprite();
};
