#include "Game.h"


//Initializers
void Game::initWindow()
{
	video_mode.height = window_height;
	video_mode.width = window_width;
	window = new sf::RenderWindow(video_mode, "TECOISC 4", sf::Style::Default);
	window->setFramerateLimit(60);
}

void Game::initVariables()
{
	running = true;
}

void Game::initStates()
{
	states.push(new MenuState(this->window, &this->states));
}

Game::Game()
{
	initWindow();
	initVariables();
	initStates();
}

Game::~Game()
{
}

bool Game::isRunning()
{
	return running;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			window->close();
			running = false; //Comment Out for Debugging
			break;
		}

		if (!states.empty()) {
			states.top()->pollEvents(this->event);
		}
	}
}

void Game::update()
{
	if (!states.empty()) {
		states.top()->update();
	}
	else {
		window->close();
		running = false;
	}
}

void Game::render()
{
	window->clear(sf::Color::Black);

	if (!states.empty()) {
		states.top()->render(this->window);
	}

	window->display();
}
