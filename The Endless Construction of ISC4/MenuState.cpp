#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	if (!font.loadFromFile("Blacklisted.ttf"))
	{
		std::cout << "Unable to load font" << std::endl;
	}
	Title.setFont(font);
	Title.setCharacterSize(50);
	Title.setFillColor(sf::Color::White);
	Title.setStyle(sf::Text::Bold);
	Title.setString("The Endless Construction of ISC4");
	Title.setPosition(500, 100);

	tutorialButton.setFillColor(sf::Color::White);
	tutorialButton.setSize(sf::Vector2f(400, 100));
	tutorialButton.setPosition(700, 250);
	easyButton.setFillColor(sf::Color::Green);
	easyButton.setSize(sf::Vector2f(400, 100));
	easyButton.setPosition(700, 400);
	normalButton.setFillColor(sf::Color::Blue);
	normalButton.setSize(sf::Vector2f(400, 100));
	normalButton.setPosition(700, 550);

	tutorialText.setFont(font);
	tutorialText.setCharacterSize(30);
	tutorialText.setFillColor(sf::Color::Black);
	tutorialText.setStyle(sf::Text::Bold);
	easyText = tutorialText;
	normalText = tutorialText;
	tutorialText.setString("Tutorial");
	tutorialText.setPosition(840, 285);
	easyText.setString("Easy");
	easyText.setPosition(870, 435);
	normalText.setString("Normal");
	normalText.setPosition(855, 585);

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

		case sf::Keyboard::Escape:
			returnState();
		}

		break;
	
	case sf::Event::MouseButtonPressed:
		mousePosWindow = sf::Mouse::getPosition(*window);
		mousePosView = window->mapPixelToCoords(this->mousePosWindow);
		switch (event.key.code) {
		case sf::Mouse::Left:
			if (tutorialButton.getGlobalBounds().contains(this->mousePosView)) {
				initState(new TutorialState(this->window, this->states));
			}
			else if (easyButton.getGlobalBounds().contains(this->mousePosView)) {
				ShellExecute(0, 0, L"https://mason.wm.edu/undergraduate/admissions/", 0, 0, SW_SHOW);
			}
			else if (normalButton.getGlobalBounds().contains(this->mousePosView)) {
				beginGame();
			}
			break;
		}
	}
}

void MenuState::update()
{
}

void MenuState::render(sf::RenderTarget* target)
{
	target->clear(sf::Color::Black);
	target->draw(Title);
	target->draw(tutorialButton);
	target->draw(easyButton);
	target->draw(normalButton);
	target->draw(tutorialText);
	target->draw(easyText);
	target->draw(normalText);
}

