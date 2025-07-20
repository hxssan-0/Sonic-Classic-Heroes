#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Camera {
private:

	//For storing chunks of levels
	Sprite* lvl_chunks;
	int num_chunks;
	int index;
	//Start is the first starting pixel count and end is the last pixel count
	float* leftPix, * rightPix;
	float cameraPos, cameraLeft, mixPix;
	//Offset = player's current position
	float* playerPos;
	float rightBoundary;

	//Function to operate on overlapping backgrounds
	void displayOverlap(RenderWindow& window);

public:

	//Constructor

	Camera(int num, float* left, float* right, float* player, Sprite* lvl, float cam = 0, int i = 0, float cameraLeft = 0, float mixPix = 0);

	//This function will run the camera and adjust for overlaps

	void runCamera(RenderWindow& window, float playerPos, float cellsX);

	float getCameraPos() const;

	float worldToWindow(float x) const;

	~Camera(); //TODO
};