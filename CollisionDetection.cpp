#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "CollisionDetection.h"
using namespace sf;
using namespace std;

//To find hit points
void CollisionDetection::findPointsObstacles(float offset_y, float offset_x) {

	bottom_left = lvl_grid[(int)(hitbox_y + pHeight + offset_y) / cell_size][(int)(hitbox_x + offset_x) / cell_size];
	left_mid = lvl_grid[(int)(hitbox_y + (pHeight / 2) + offset_y) / cell_size][(int)(hitbox_x + offset_x) / cell_size];
	right_mid = lvl_grid[(int)(hitbox_y + (pHeight / 2) + offset_y) / cell_size][(int)(hitbox_x + offset_x + pWidth) / cell_size];
	bottom_right = lvl_grid[(int)(hitbox_y + pHeight + offset_y) / cell_size][(int)(hitbox_x + offset_x + pWidth) / cell_size];

	top_left = lvl_grid[(int)(hitbox_y + offset_y) / cell_size][(int)(hitbox_x + offset_x) / cell_size];
	top_right = lvl_grid[(int)(hitbox_y + offset_y) / cell_size][(int)(hitbox_x + offset_x + pWidth) / cell_size];
	top_mid = lvl_grid[(int)(hitbox_y + offset_y) / cell_size][(int)(hitbox_x + offset_x + pWidth / 2) / cell_size];
}

void CollisionDetection::findPointsCollectibles(float offset_y, float offset_x) {

	bottom_left = collectibles_grid[(int)(hitbox_y + pHeight + offset_y) / cell_size][(int)(hitbox_x + offset_x) / cell_size];
	left_mid = collectibles_grid[(int)(hitbox_y + (pHeight / 2) + offset_y) / cell_size][(int)(hitbox_x + offset_x) / cell_size];
	right_mid = collectibles_grid[(int)(hitbox_y + (pHeight / 2) + offset_y) / cell_size][(int)(hitbox_x + offset_x + pWidth) / cell_size];
	bottom_right = collectibles_grid[(int)(hitbox_y + pHeight + offset_y) / cell_size][(int)(hitbox_x + offset_x + pWidth) / cell_size];

	top_left = collectibles_grid[(int)(hitbox_y + offset_y) / cell_size][(int)(hitbox_x + offset_x) / cell_size];
	top_right = collectibles_grid[(int)(hitbox_y + offset_y) / cell_size][(int)(hitbox_x + offset_x + pWidth) / cell_size];
	top_mid = collectibles_grid[(int)(hitbox_y + offset_y) / cell_size][(int)(hitbox_x + offset_x + pWidth / 2) / cell_size];
}

	//Constructor
CollisionDetection::CollisionDetection(int box_x, int box_y, int height, int width, int size, char** grid, char** collectibles) : lvl_grid(grid), collectibles_grid(collectibles) {
		hitbox_x = box_x;
		hitbox_y = box_y;
		pHeight = height;
		pWidth = width;
		cell_size = size;

		ringBuffer.loadFromFile("Sprites\\Sounds\\Global\\Ring.wav");
		ringSound.setBuffer(ringBuffer);

		bottom_left = '\0';
		bottom_right = '\0';
		bottom_mid = '\0';
		top_left = '\0';
		top_right = '\0';
		top_mid = '\0';
		right_mid = '\0';
		left_mid = '\0';
	}

void CollisionDetection::detectCollision(float offset_x, float offset_y, bool& moveRight, bool& moveLeft, bool& moveUp, bool& moveDown, bool& onSpike, bool& quickJump, bool& pitFound, bool knucklesActive) {
	findPointsObstacles(offset_y, offset_x);
	if ((bottom_left == 'w' && left_mid == 'w')) {
		moveLeft = false;
	}
	else if ((bottom_left == 'b' || left_mid == 'b')) {
		moveLeft = false;
		if (knucklesActive) {
			int i = (int)(offset_y + hitbox_y + pHeight / 2) / cell_size;
			int j = (int)(offset_x + hitbox_x + pWidth / 2) / cell_size;
			if (lvl_grid[i][j] == 'b') {
				lvl_grid[i][j] = 'e';
			}
			if (lvl_grid[i][j - 1] == 'b') {
				lvl_grid[i][j - 1] = 'e';
			}
		}
	}
	else if ((bottom_left == 's' || left_mid == 's') && onSpike == false) {
		moveLeft = false;
	}

	if ((bottom_right == 'w' && right_mid == 'w')) {
		moveRight = false;
	}
	else if ((bottom_right == 'b' || right_mid == 'b')) {
		moveRight = false;
		if (knucklesActive) {
			int i = (int)(offset_y + hitbox_y + pHeight / 2) / cell_size;
			int j = (int)(offset_x + hitbox_x + pWidth / 2) / cell_size;
			if (lvl_grid[i][j] == 'b') {
				lvl_grid[i][j] = 'e';
			}
			//had to check adjacent cell due to off by one error
			if (lvl_grid[i][j + 1] == 'b') {
				lvl_grid[i][j + 1] = 'e';
			}
		}
	}
	else if ((bottom_right == 's' || right_mid == 's') && onSpike == false) {
		moveRight = false;
	}

	if (bottom_left == 'h' || bottom_right == 'h' || bottom_mid == 'h') {
		pitFound = true;

	}

	if (top_right == 'w' || top_left == 'w' || top_mid == 'w') {
		moveUp = false;
	}

	if (top_mid == 'p') {
		quickJump = true;
	}

	if (bottom_left == 'p' || bottom_right == 'p' || bottom_mid == 'p') {
		moveDown = false;
	}
	else {
		moveDown = true;
	}
}

void CollisionDetection::checkItem(float offset_x, float offset_y, int& rings, int& health, int vol, bool& boostFound)
{
	findPointsCollectibles(offset_y, offset_x);
	//since i want the items at that grid position to disappear, i have to convert back to row/column
	//by finding the center of the hitbox
	int i = (int)(offset_y + hitbox_y + pHeight / 2) / cell_size;
	int j = (int)(offset_x + hitbox_x + pWidth / 2) / cell_size;
	if (bottom_left == 'r' || left_mid == 'r') {
		if (collectibles_grid[i][j] == 'r') {
			collectibles_grid[i][j] = 'e';
			ringSound.setVolume(vol);
			ringSound.play();
			rings++;
		}
	}
	if (bottom_right == 'r' || right_mid == 'r') {
		if (collectibles_grid[i][j] == 'r') {
			collectibles_grid[i][j] = 'e';
			ringSound.setVolume(vol);
			ringSound.play();
			rings++;
		}
	}
	if (top_left == 'r' || top_mid == 'r' || top_right == 'r') {
		if (collectibles_grid[i][j] == 'r') {
			collectibles_grid[i][j] = 'e';
			ringSound.setVolume(vol);
			ringSound.play();
			rings++;
		}
	}

	if (bottom_left == 'b' || left_mid == 'b') {
		if (collectibles_grid[i][j] == 'b') {
			boostFound = true;
			collectibles_grid[i][j] = 'e';
		}
	}
	if (bottom_right == 'b' || right_mid == 'b') {
		if (collectibles_grid[i][j] == 'b') {
			boostFound = true;
			collectibles_grid[i][j] = 'e';
		}
	}
	if (top_left == 'b' || top_mid == 'b' || top_right == 'b') {
		if (collectibles_grid[i][j] == 'b') {
			boostFound = true;
			collectibles_grid[i][j] = 'e';
		}
	}

	if (bottom_left == 'h' || left_mid == 'h') {
		if (collectibles_grid[i][j] == 'h') {
			collectibles_grid[i][j] = 'e';
			health++;
		}
	}
	if (bottom_right == 'h' || right_mid == 'h') {
		if (collectibles_grid[i][j] == 'h') {
			collectibles_grid[i][j] = 'e';
			health++;
		}
	}
	if (top_left == 'h' || top_mid == 'h' || top_right == 'h') {
		if (collectibles_grid[i][j] == 'h') {
			collectibles_grid[i][j] = 'e';
			health++;
		}
	}
}

void CollisionDetection::findPointsInt(int offset_y, int offset_x) {

	//First finding absolute distance or magnitude for each hitbox point from origin which will be compared with
	// the player's hitbox points distance from origin in magnitude
	//Im treating each hitbox point in x,y coordinate wrt enemy/player's obj parameters

	left = offset_x - hitbox_x;
	right = offset_x + hitbox_x;
	top = offset_y - hitbox_y;
	bottom = offset_y + hitbox_y;

}

bool CollisionDetection::checkEnemy(CollisionDetection player_collision, int player_x, int player_y, int enemy_x, int enemy_y) {

	// Calculating hitboxes
	player_collision.findPointsInt(player_y, player_x);
	findPointsInt(enemy_y, enemy_x);

	if ((player_collision.left < right) && ((player_collision.right > left)) && ((player_collision.bottom > top)) && ((player_collision.top < bottom))) {
		return true;
	}
	return false;

}