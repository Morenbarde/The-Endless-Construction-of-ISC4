#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "MenuState.h"

class Game
{
private:

	sf::VideoMode video_mode;
	sf::RenderWindow* window;
	int window_height = 800;
	int window_width = 1800;

	sf::Event event;

	bool running;

	std::stack<State*> states;

	//Initilizers
	void initWindow();
	void initVariables();
	void initStates();

protected:

public:
	Game();
	~Game();

	bool isRunning();

	void pollEvents();
	void update();
	void render();

};

