#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;


class CollisionDetection {
private:
	int hitbox_x, hitbox_y, pHeight, pWidth;
	int cell_size;
	char** lvl_grid;
	char** collectibles_grid;
	char bottom_left, bottom_right, bottom_mid, top_left, top_right, top_mid, right_mid, left_mid;
	int left, right, top, bottom;

	SoundBuffer ringBuffer;
	Sound ringSound;

	//To find hit points
	void findPointsObstacles(float offset_y, float offset_x);
	void findPointsCollectibles(float offset_y, float offset_x);
	void findPointsInt(int offset_y, int offset_x);

public:

	//Constructor
	CollisionDetection(int box_x, int box_y, int height, int width, int size, char** grid, char** collectibles);

	void detectCollision(float offset_x, float offset_y, bool& moveRight, bool& moveLeft, bool& moveUp, bool& moveDown, bool& onSpike, bool& quickJump, bool& pitFound, bool knuclesActive = false);

	void checkItem(float offset_x, float offset_y, int& rings, int& health, int vol, bool& boostFound);

	bool checkEnemy(CollisionDetection player_collision, int player_x, int player_y, int enemy_x, int enemy_y);

};