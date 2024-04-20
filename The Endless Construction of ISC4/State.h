#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <stack>

class State
{
private:
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;

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
	}

	virtual ~State() {};

	virtual void pollEvents(sf::Event event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};