#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "CollectiblesFactory.h"
#include "Health.h"

class HealthFactory : public CollectiblesFactory {
private:
	Health* health;
public:
	virtual void createCollectible(int x, int y);
	virtual Collectibles& getCollectible();
	~HealthFactory();
};

