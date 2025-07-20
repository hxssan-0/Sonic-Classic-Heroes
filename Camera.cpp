#pragma once
#include<iostream>
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;


	//Function to operate on overlapping backgrounds
	void Camera::displayOverlap(RenderWindow& window) {
		mixPix = (cameraPos + 1200) - leftPix[index];
		lvl_chunks[index + 1].setTextureRect(IntRect(0, 0, mixPix, 896));


		lvl_chunks[index + 1].setPosition(rightPix[index] - cameraPos, 0);
		window.draw(lvl_chunks[index + 1]);
	}

	//Constructor

	Camera::Camera(int num, float* left, float* right, float* player, Sprite* lvl, float cam, int i, float cameraLeft, float mixPix) : lvl_chunks(lvl) {
		num_chunks = num;
		leftPix = new float[num_chunks];
		rightPix = new float[num_chunks];
		for (int i = 0; i < num_chunks; i++) {
			leftPix[i] = left[i];
			rightPix[i] = right[i];
		}
		playerPos = new float;
		*playerPos = *player;
		cameraPos = cam;
		index = i;
		this->cameraLeft = cameraLeft;
		this->mixPix = mixPix;
		rightBoundary = rightPix[num_chunks - 1];
	}

	//This function will run the camera and adjust for overlaps

void Camera::runCamera(RenderWindow& window, float playerPos, float cellsX) {
	//updating the index first and then drawing the background to prevent flickering when
	// transitioning between chunks
	cameraPos = playerPos;
	if (cameraPos < 0.0f)
		cameraPos = 0.0f;
	//camera doesnt go beyond the right boundary
	if (cameraPos > rightBoundary - 1200)
		cameraPos = rightBoundary - 1200;

	if (cameraPos > rightPix[index] && index < num_chunks - 1) {
		index++;
	}
	else if (cameraPos < leftPix[index] && index >= 0) {
		index--;
	}

	if (cameraPos >= leftPix[index] && cameraPos <= rightPix[index] && index < num_chunks - 1) {
		cameraLeft = cameraPos - leftPix[index];

		lvl_chunks[index].setTextureRect(IntRect(cameraLeft, 0, 1200, 896));
		lvl_chunks[index].setPosition(0, 0);
		window.draw(lvl_chunks[index]);
		//If we exceed the pixel range for current boundary
		if (cameraPos + 1200 > rightPix[index]) {
			displayOverlap(window);
		}
	}

}

float Camera::getCameraPos() const
{
	return cameraPos;
}

float Camera::worldToWindow(float x) const
{
	return x - cameraPos + 600.0f;
}