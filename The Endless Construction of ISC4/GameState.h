#pragma once
#include "State.h"
#include "EndState.h"
#include "craneArm.h"
#include "Beam.h"
#include "Floor.h"

class GameState :
    public State
{
private:

    b2Vec2 gravity;
    b2World* world;
    std::vector<GameObject*> game_objects;
    Crane* crane;
    b2Body* groundBody;
    sf::Texture groundTexture;
    sf::Sprite groundSprite;
    sf::Texture craneTexture;
    sf::Sprite craneSprite;
    sf::Texture clawdiusTexture;
    sf::Sprite clawdiusSprite;

    sf::Text scoreText;
    sf::Text beamsText;
    sf::Text floorsText;
    sf::Font font;

    int maxBeams = 8;
    int maxFloors = 4;
    int remainingBeams;
    int remainingFloors;

    
    void initVariables();
    void initGameWorld();
    void initGameObjects();
    void createGround(float posX, float posY, float width, float height);
    void attatchBeam();
    void attatchFloor();
    void breakAttatchment();
    void nextLevel();
protected:
public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);

    void endGame();

    void pollEvents(sf::Event event);
    void update();
    void render(sf::RenderTarget* target);
};

