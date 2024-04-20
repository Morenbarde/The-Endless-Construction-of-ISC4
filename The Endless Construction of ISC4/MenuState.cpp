#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
}

void MenuState::beginGame()
{
	initState(new GameState(this->window, this->states));
}

void MenuState::pollEvents(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code) {

		case sf::Keyboard::Enter:
			beginGame();
			break;
		}
		break;
	}
}

void MenuState::update()
{
}

void MenuState::render(sf::RenderTarget* renderer)
{
	window->clear(sf::Color::Magenta);
}

