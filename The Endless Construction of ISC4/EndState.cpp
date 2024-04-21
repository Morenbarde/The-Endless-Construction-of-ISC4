#include "EndState.h"

EndState::EndState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
}

void EndState::pollEvents(sf::Event event)
{
}

void EndState::update()
{
}

void EndState::render(sf::RenderTarget* target)
{
}
