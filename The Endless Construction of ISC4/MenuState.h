#pragma once

#include "State.h"
#include "GameState.h"
#include "TutorialState.h"
#include <Windows.h>
#include <shellapi.h>

class MenuState :
    public State
{

private:
    sf::Font font;
    sf::Text Title;
    sf::Text tutorialText;
    sf::Text easyText;
    sf::Text normalText;
    sf::RectangleShape tutorialButton;
    sf::RectangleShape easyButton;
    sf::RectangleShape normalButton;

    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
protected:
public:
    MenuState(sf::RenderWindow* window, std::stack<State*>* states);

    void beginGame();

    void pollEvents(sf::Event event);
    void update();
    void render(sf::RenderTarget* target);
};
