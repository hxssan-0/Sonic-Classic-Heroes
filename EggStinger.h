#pragma once
#include <iostream>
#include "Flyers.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

class EggStinger : public Flyers
{
	Texture spikeTex;
	Sprite spikeSprite;
	int spikeX;
	int spikeY;
	int eggWidth;
	int eggHeight;
	int eggSpikeWidth;
	int eggSpikeHeight;
	Clock attack;
	Clock delayClock;
	Clock dtt;
	bool attackP = false;
	bool mR = true;
	bool mL = false;
	bool moveToTarget;
	bool findTarget;
	bool reverse;
	bool original;
	bool delay;
	int target_x;
	int target_y;
	int reverse_y;
	CollisionDetection* cdSpike;
public:
	EggStinger(float eX, float eY);

	virtual void moveEnemy(float dt, float targetX = 0, float targetY = 0);

	virtual void update(float dt, float x, RenderWindow& window, float targetX = 0, float targetY = 0, float gravity = 0, float vol = 0, char** lvl = nullptr);

	void moveBoss(float& boss_x, float& boss_y, Sprite& bossSprite, bool& mL, bool& mR);

	void moveBoss(float& boss_x, float& boss_y, int target_x, Sprite& bossSprite, bool& moveToTarget);

	void findPlayer(float player_x, float player_y, int& target_x, int& target_y, int gridHeight, char** lvl);

	void spikeOut(float boss_x, float boss_y, int& spike_x, int& spike_y, int bossHeight, int spikeHeight, Sprite& spike);

	void attackPlayer(float& boss_x, float& boss_y, int& spike_x, int& spike_y, int& target_y, int& target_x, Sprite& spike, Sprite& boss, int spikeHeight, char** lvl, bool& reverse, bool& delay);

	void reverseBoss(float& boss_x, float& boss_y, int reverse_y, Sprite& boss, bool& reverse, bool& attack, bool& moveToTarget, bool& findTarget, bool& original);

	void spikeIn(float& boss_x, float& boss_y, int& spike_x, int& spike_y, int bossHeight, int spikeHeight, Sprite& spike);

	virtual Sprite& getNeedleSprite();
};
