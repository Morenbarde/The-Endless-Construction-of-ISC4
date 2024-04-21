#pragma once
#include "GameObject.h"
class Floor :
    public GameObject
{
private:

    float width = 350;
    float height = 20;
    void updateSprite();
protected:
public:
    Floor(b2World* world, float posX, float posY);
    void update();
    void render(sf::RenderTarget* target);
};

