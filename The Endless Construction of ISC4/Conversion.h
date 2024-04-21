#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

const static float scale = 50.f;

class Conversion
{
public:

    static float metersToPixels(float meters)
    {
        return meters * scale;
    }

    static sf::Vector2f metersToPixels(b2Vec2 vec)
    {
        return boxToSfmlVec(vec) * scale;
    }

    static float pixelsToMeters(float pixels)
    {
        return pixels / scale;
    }

    static b2Vec2 pixelsToMeters(sf::Vector2f vec)
    {
        return sfmlToBoxVec(vec / scale);
    }

    static sf::Vector2f boxToSfmlVec(b2Vec2 vec)
    {
        return sf::Vector2f(vec.x, vec.y);
    }

    static b2Vec2 sfmlToBoxVec(sf::Vector2f vec)
    {
        return b2Vec2(vec.x, vec.y);
    }

};

