#pragma once

#include "State.h"
#include "GameState.h"

class MenuState :
    public State
{

private:
protected:
public:
    MenuState(sf::RenderWindow* window, std::stack<State*>* states);

    void beginGame();

    void pollEvents(sf::Event event);
    void update();
    void render(sf::RenderTarget* renderer);
};
