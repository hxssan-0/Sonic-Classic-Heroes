#pragma once
#include <iostream>
#include "Obstacles.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

//'e' for nothing or empty space
//'s' for spikes
//'w' for walls/ground
//'b' for breakable wall
//'p' for platforms
//'h' for pits (hollow)

Obstacles::Obstacles(int cX, int cY) : obstacles(new char*[cY]) {
	cellsX = cX;
	cellsY = cY;
	for (int i = 0; i < cY; i++) {
		obstacles[i] = new char[cX];
		for (int j = 0; j < cX; j++)
			obstacles[i][j] = 'e';
	}
}

void Obstacles::createObstacle(int i, int j, char o)
{
	obstacles[i][j] = o;
}

bool Obstacles::checkObstacle(int i, int j, char o) const
{
	return obstacles[i][j] == o;
}

char** Obstacles::getObstacles()
{
	return obstacles;
}