#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "CollectiblesFactory.h"
#include "Boost.h"

class BoostFactory : public CollectiblesFactory {
private:
	Boost* boost;
public:
	virtual void createCollectible(int x, int y);
	virtual Collectibles& getCollectible();
	~BoostFactory();
};

