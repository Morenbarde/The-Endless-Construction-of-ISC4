#pragma once
#include "State.h"
class GameState :
    public State
{
private:
protected:
public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);

    void endGame();

    void pollEvents(sf::Event event);
    void update();
    void render(sf::RenderTarget* renderer);
};

