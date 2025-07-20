#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Collectibles.h"

class CollectiblesFactory {
public:
	virtual void createCollectible(int x, int y) = 0;
	virtual Collectibles& getCollectible() = 0;
	virtual ~CollectiblesFactory();
};