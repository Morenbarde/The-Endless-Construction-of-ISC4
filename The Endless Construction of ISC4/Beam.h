#pragma once
#include "GameObject.h"
class Beam :
    public GameObject
{
private:

    float width = 25;
    float height = 200;
    void updateSprite();
protected:
public:
    Beam(b2World* world, float posX, float posY);
    void update();
    void render(sf::RenderTarget* target);
};

