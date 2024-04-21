#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Conversion.h"

class GameObject
{
private:
protected:
	sf::Texture texture;
	b2Body* body;
	sf::Sprite sprite;
	sf::Vector2f position;

public:
	float scale = 30.f;

	inline sf::Sprite getSprite() { return sprite; }
	inline b2Body* getBody() { return body;  }

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;

};

