#include "Beam.h"

void Beam::updateSprite()
{
    sprite.setPosition(Conversion::metersToPixels(body->GetPosition()));
    sprite.setRotation(body->GetAngle() * 180 / b2_pi);
}

Beam::Beam(b2World* world, float posX, float posY)
{
    position = sf::Vector2f(posX, posY);
    
    texture.loadFromFile("beam.png");

    b2BodyDef bodyDef;
    bodyDef.position = Conversion::pixelsToMeters(position);
    bodyDef.type = b2_dynamicBody;
    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(Conversion::pixelsToMeters(width / 2), Conversion::pixelsToMeters(height / 2));
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.2f;
    fixtureDef.friction = 0.7f;
    fixtureDef.restitution = 0.1f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    sprite.setTexture(texture);
    sprite.setScale(width / texture.getSize().x, height / texture.getSize().y);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    updateSprite();
}

void Beam::update()
{
    updateSprite();
}

void Beam::render(sf::RenderTarget* target)
{
    target->draw(sprite);
}
