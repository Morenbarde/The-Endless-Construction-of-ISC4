#include "Conversion.h"

float Conversion::metersToPixels(float meters)
{
    return meters*scale;
}

float Conversion::pixelsToMeters(float pixels)
{
    return pixels/scale;
}

sf::Vector2f Conversion::boxToSfmlVec(b2Vec2 vec)
{
    return sf::Vector2f(vec.x, vec.y);
}

b2Vec2 Conversion::sfmlToBoxVec(sf::Vector2f vec, float width, float height)
{
    return b2Vec2(vec.x, vec.y);
}

sf::Vector2f Conversion::boxPosToSFMLPos(b2Vec2 vec, float width, float height)
{
    return sf::Vector2f((vec.x - width / 2), (vec.x - height / 2));
}

b2Vec2 Conversion::sfmlPosToBoxPos(sf::Vector2f vec, float width, float height)
{
    return b2Vec2((vec.x + width / 2), (vec.x + height / 2));
}
