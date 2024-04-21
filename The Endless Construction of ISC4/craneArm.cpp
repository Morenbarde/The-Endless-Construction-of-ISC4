#include "craneArm.h"

void Crane::updateSprites()
{
    armsprite.setPosition(Conversion::metersToPixels(armbody->GetPosition()));
    armsprite.setRotation(armbody->GetAngle() * 180 / b2_pi);
    jointsprite.setPosition(Conversion::metersToPixels(jointbody->GetPosition()));
    jointsprite.setRotation(jointbody->GetAngle() * 180 / b2_pi);
}

Crane::Crane(b2World* world, float posX, float posY)
{
    rotating = false;
    beamAttatched = false;

    position = sf::Vector2f(posX, posY);
    armtexture.loadFromFile("craneArm.png");
    jointtexture.loadFromFile("craneJoint.png");

    b2BodyDef bodyDef;
    bodyDef.position = Conversion::pixelsToMeters(position);
    bodyDef.type = b2_dynamicBody;
    bodyDef.gravityScale = 0;
    armbody = world->CreateBody(&bodyDef);
    bodyDef.type = b2_staticBody;
    jointbody = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(Conversion::pixelsToMeters(width/2), Conversion::pixelsToMeters(height/2));
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 1.f;
    fixtureDef.restitution = 0.3f;
    fixtureDef.shape = &shape;
    armbody->CreateFixture(&fixtureDef);

    shape.SetAsBox(Conversion::pixelsToMeters(50 / 2), Conversion::pixelsToMeters(50 / 2));
    fixtureDef.shape = &shape;
    jointbody->CreateFixture(&fixtureDef);

    b2WheelJointDef wheelJointDef;
    wheelJointDef.bodyA = armbody;
    wheelJointDef.bodyB = jointbody;
    wheelJointDef.collideConnected = false;
    wheelJointDef.localAnchorA = armbody->GetLocalCenter();
    wheelJointDef.localAnchorB = jointbody->GetLocalCenter();
    joint = (b2WheelJoint*)world->CreateJoint(&wheelJointDef);
    joint->SetLimits(-800, 800);
    joint->EnableLimit(true);

    armsprite.setTexture(armtexture);
    armsprite.setScale(width / armtexture.getSize().x, height / armtexture.getSize().y);
    armsprite.setOrigin(armsprite.getLocalBounds().width / 2, armsprite.getLocalBounds().height / 2);
    jointsprite.setTexture(jointtexture);
    jointsprite.setOrigin(jointsprite.getLocalBounds().width / 2, jointsprite.getLocalBounds().height / 2);
    updateSprites();
}

void Crane::rotate(int dir)
{
    if ((armbody->GetAngle() >= b2_pi / 4 && dir > 0) || (armbody->GetAngle() <= -b2_pi / 4 && dir < 0)) {
        haltRotation();
    }
    else {
        armbody->SetAngularVelocity(rotatespeed * dir);
    }
}

void Crane::haltRotation()
{
    rotating = false;
    armbody->SetAngularVelocity(0);
}

void Crane::extend(int dir)
{
    sf::Vector2f pixelcoords = Conversion::metersToPixels(armbody->GetPosition());
    if ((pixelcoords.x - position.x > 500 && dir > 0) || (position.x - pixelcoords.x > 500 && dir < 0)) {
        armbody->SetLinearVelocity(b2Vec2(0, 0));
    }
    else {
        float totalV = extendspeed * dir;
        float angle = armbody->GetAngle();
        float xchange = cosf(angle) * totalV;
        float ychange = sinf(angle) * totalV;
        armbody->SetLinearVelocity(b2Vec2(xchange, ychange));
    }
}

void Crane::attatchBeam(b2World* world, b2Body* beam)
{
    b2DistanceJointDef jointDef;
    jointDef.bodyA = armbody;
    jointDef.bodyB = beam;
    jointDef.collideConnected = false;
    float armXoffset = cosf(armbody->GetAngle()) * Conversion::pixelsToMeters(900);
    float armYoffset = sinf(armbody->GetAngle()) * Conversion::pixelsToMeters(900);
    jointDef.localAnchorA = b2Vec2(armbody->GetLocalCenter().x - Conversion::pixelsToMeters(900), 0);
    jointDef.localAnchorB = b2Vec2(beam->GetLocalCenter().x, beam->GetLocalCenter().y+2);
    jointDef.maxLength = 2;
    jointDef.minLength = 2;
    beamJoint = (b2DistanceJoint*)world->CreateJoint(&jointDef);
    beamAttatched = true;
}

void Crane::attatchFloor(b2World* world, b2Body* floor)
{
    b2DistanceJointDef jointDef;
    jointDef.bodyA = armbody;
    jointDef.bodyB = floor;
    jointDef.collideConnected = false;
    float armXoffset = cosf(armbody->GetAngle()) * Conversion::pixelsToMeters(900);
    //float armYoffset = sinf(armbody->GetAngle()) * Conversion::pixelsToMeters(900);
    jointDef.localAnchorA = b2Vec2(armbody->GetLocalCenter().x - Conversion::pixelsToMeters(900), 0);
    jointDef.localAnchorB = b2Vec2(floor->GetLocalCenter().x-1, 0);
    jointDef.maxLength = 2;
    jointDef.minLength = 2;
    leftFloorJoint = (b2DistanceJoint*)world->CreateJoint(&jointDef);
    jointDef.localAnchorB = b2Vec2(floor->GetLocalCenter().x + 1, 0);
    rightFloorJoint = (b2DistanceJoint*)world->CreateJoint(&jointDef);
    floorAttatched = true;
}

void Crane::detatch(b2World* world)
{
    if (beamAttatched) {
        world->DestroyJoint(beamJoint);
        beamJoint = nullptr;
        beamAttatched = false;
    }
    else if (floorAttatched) {
        world->DestroyJoint(leftFloorJoint);
        world->DestroyJoint(rightFloorJoint);
        leftFloorJoint = nullptr;
        rightFloorJoint = nullptr;
        floorAttatched = false;
    }
}

void Crane::update()
{
    updateSprites();
}

void Crane::render(sf::RenderTarget* target)
{
    target->draw(armsprite);
    target->draw(jointsprite);
}
