#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

class Obstacles
{
private:
	int cellsX;
	int cellsY;
	char** obstacles;
public:
	Obstacles(int cX, int cY);

	void createObstacle(int i, int j, char o);

	bool checkObstacle(int i, int j, char o) const;

	char** getObstacles();
};