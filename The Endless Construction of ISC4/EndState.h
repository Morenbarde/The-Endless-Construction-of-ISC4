#pragma once
#include "State.h"
class EndState :
    public State
{
private:
protected:
public:
    EndState(sf::RenderWindow* window, std::stack<State*>* states);

    void pollEvents(sf::Event event);
    void update();
    void render(sf::RenderTarget* target);
};

