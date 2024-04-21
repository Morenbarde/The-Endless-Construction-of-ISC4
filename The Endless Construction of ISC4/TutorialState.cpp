#include "TutorialState.h"

TutorialState::TutorialState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	texture.loadFromFile("tutorial1.png");
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
}

void TutorialState::incrementPage() {
	currentpage++;
	if (!texture.loadFromFile("tutorial" + std::to_string(currentpage) + ".png")) {
		returnState();
	}
	else {
		sprite.setTexture(texture);
	}
}

void TutorialState::pollEvents(sf::Event event) {
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code) {

		case sf::Keyboard::Escape:
			returnState();
			break;
		case sf::Keyboard::Enter:
			incrementPage();
			break;
		}
	}
}

void TutorialState::update() {

}

void TutorialState::render(sf::RenderTarget* target) {
	target->draw(sprite);
}