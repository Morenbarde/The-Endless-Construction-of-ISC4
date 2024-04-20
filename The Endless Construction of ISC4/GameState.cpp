#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
}

void GameState::endGame()
{
	returnState();
}

void GameState::pollEvents(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code) {

		case sf::Keyboard::Escape:
			endGame();
		}
		break;
	}
}

void GameState::update()
{
}

void GameState::render(sf::RenderTarget* renderer)
{
	window->clear(sf::Color::Blue);
}
