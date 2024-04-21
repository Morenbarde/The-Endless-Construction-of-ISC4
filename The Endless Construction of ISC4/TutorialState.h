#pragma once

#include "State.h"
#include "GameState.h"

class TutorialState :
    public State
{

private:
    sf::Texture texture;
    sf::Sprite sprite;
    int currentpage;
protected:
public:
    TutorialState(sf::RenderWindow* window, std::stack<State*>* states);

    void incrementPage();

    void pollEvents(sf::Event event);
    void update();
    void render(sf::RenderTarget* target);
};