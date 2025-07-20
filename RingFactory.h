#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "CollectiblesFactory.h"
#include "Ring.h"

class RingFactory : public CollectiblesFactory {
private:
	Ring* ring;
public:
	virtual void createCollectible(int x, int y);
	virtual Collectibles& getCollectible();
	~RingFactory();
};
