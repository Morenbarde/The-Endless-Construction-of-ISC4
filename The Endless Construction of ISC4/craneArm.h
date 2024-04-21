#pragma once
#include "GameObject.h"
class Crane
{
private:
    float width = 2000;
    float height = 30;

    sf::Texture armtexture;
    b2Body* armbody;
    sf::Sprite armsprite;
    sf::Texture jointtexture;
    b2Body* jointbody;
    sf::Sprite jointsprite;
    sf::Vector2f position;

    b2WheelJoint* joint;
    b2DistanceJoint* beamJoint;
    b2DistanceJoint* leftFloorJoint;
    b2DistanceJoint* rightFloorJoint;



    float rotatespeed = 0.2f;
    float extendspeed = 2.f;
    bool rotating;
    int rotatedir;
    bool extending;
    int extenddir;

    bool beamAttatched;
    bool floorAttatched;

    void updateSprites();
protected:
public:
    Crane(b2World* world, float posX, float posY);

    void rotate(int dir);
    void haltRotation();
    void extend(int dir);

    sf::Sprite getArmSprite() {
        return armsprite;
    }
    sf::Sprite getJointSprite() {
        return jointsprite;
    }
    bool isBeamAttatched() {
        return beamAttatched;
    }
    bool isFloorAttatched() {
        return floorAttatched;
    }
    void attatchBeam(b2World* world, b2Body* beam);
    void attatchFloor(b2World* world, b2Body* floor);
    void detatch(b2World* world);

    void update();
    void render(sf::RenderTarget* target);
};

