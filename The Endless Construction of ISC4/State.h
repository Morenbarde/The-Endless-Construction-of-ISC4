#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <box2d/box2d.h>

#include <iostream>
#include <stack>

#include "Conversion.h"

class State
{
private:
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	int score;
	sf::Font font;

	//State Manager Functions
	void returnState() {
		states->pop();
	}

	void initState(State* state) {
		states->push(state);
	}

public:
	State(sf::RenderWindow* window, std::stack<State*>* states) {
		this->window = window;
		this->states = states;
		score = 0;
	}

	virtual ~State() {};

	virtual void pollEvents(sf::Event event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};