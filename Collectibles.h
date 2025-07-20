#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Collectibles
{
protected:
	//Animations* animations;
	float x, y;
	Texture itemTex;
	Sprite itemSprite;

public:
	Collectibles(int x, int y);

	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	Sprite& getSprite();

};