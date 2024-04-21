#include "GameState.h"

void GameState::initVariables()
{
	if (!font.loadFromFile("Blacklisted.ttf"))
	{
		std::cout << "Unable to load font" << std::endl;
	}
	remainingBeams = maxBeams;
	remainingFloors = maxFloors;
	score = 0;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setStyle(sf::Text::Bold);
	beamsText = scoreText;
	floorsText = scoreText;

	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setPosition(10, 10);
	beamsText.setString("Remaining Beams: " + std::to_string(remainingBeams));
	beamsText.setPosition(10, 50);
	floorsText.setString("Remaining Floors: " + std::to_string(remainingFloors));
	floorsText.setPosition(10, 90);

	craneTexture.loadFromFile("crane.png");
	craneSprite.setTexture(craneTexture);
	craneSprite.setScale(1.5, 1.5);
	craneSprite.setPosition(1600, 150);

	clawdiusTexture.loadFromFile("clawdius.png");
	clawdiusSprite.setTexture(clawdiusTexture);
	clawdiusSprite.setScale(0.13, 0.13);
	clawdiusSprite.setPosition(1680, 165);
}

void GameState::initGameWorld()
{
	gravity = b2Vec2(0.f, 9.8f);
	world = new b2World(gravity);
}

void GameState::initGameObjects()
{
	createGround(800.f, 750.f, 5000.f, 100.f);
	crane = new Crane(world, 1650, 300);
}

void GameState::createGround(float posX, float posY, float width, float height)
{
	sf::Vector2f position = sf::Vector2f(posX, posY);
	b2BodyDef bodyDef;
	bodyDef.position = Conversion::pixelsToMeters(position);
	bodyDef.type = b2_staticBody;
	groundBody = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(Conversion::pixelsToMeters(width/2), Conversion::pixelsToMeters(height/2));
	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.f;
	fixtureDef.shape = &shape;
	groundBody->CreateFixture(&fixtureDef);

	groundTexture.loadFromFile("ground.png");
	groundSprite.setTexture(groundTexture);
	groundSprite.setScale(width / groundTexture.getSize().x, height / groundTexture.getSize().y);
	groundSprite.setOrigin(groundSprite.getLocalBounds().width / 2, groundSprite.getLocalBounds().height / 2);
	groundSprite.setPosition(position);
	groundSprite.setRotation(groundBody->GetAngle() * 180 / b2_pi);
	
}

void GameState::attatchBeam()
{
	if (!crane->isBeamAttatched() && !crane->isFloorAttatched() && remainingBeams > 0) {
		Beam* beam = new Beam(world, 0, 0);
		crane->attatchBeam(world, beam->getBody());
		game_objects.push_back(beam);
		remainingBeams--;
	}
}

void GameState::attatchFloor()
{
	if (!crane->isBeamAttatched() && !crane->isFloorAttatched() && remainingFloors > 0) {
		Floor* floor = new Floor(world, 0, 0);
		crane->attatchFloor(world, floor->getBody());
		game_objects.push_back(floor);
		remainingFloors--;
	}
}

void GameState::breakAttatchment()
{
	crane->detatch(world);
}

void GameState::nextLevel()
{
	if (!crane->isBeamAttatched() && !crane->isFloorAttatched()) {
		groundBody->SetType(b2_staticBody);
		groundBody->SetTransform(b2Vec2(groundBody->GetPosition().x, groundBody->GetPosition().y+Conversion::pixelsToMeters(200)), groundBody->GetAngle());
		bool gameEnd = true;
		for (auto& element : game_objects) {
			element->getBody()->SetType(b2_staticBody);
			element->getBody()->SetTransform(b2Vec2(element->getBody()->GetPosition().x, element->getBody()->GetPosition().y+Conversion::pixelsToMeters(200)), element->getBody()->GetAngle());
			element->update();
			if (element->getSprite().getGlobalBounds().top < 800) {
				gameEnd = false;
				score += 10;
			}
		}
		if (!gameEnd) {
			score += 100;
			remainingBeams = maxBeams;
			remainingFloors = maxFloors;
		}
		else {
			endGame();
		}
		
	}
}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	initVariables();
	initGameWorld();
	initGameObjects();
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
			break;
		case sf::Keyboard::B:
			attatchBeam();
			break;
		case sf::Keyboard::F:
			attatchFloor();
			break;
		case sf::Keyboard::Space:
			breakAttatchment();
			break;
		case sf::Keyboard::Tab:
			nextLevel();
			break;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		crane->rotate(1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		crane->rotate(-1);
	}
	else {
		crane->rotate(0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		crane->extend(-1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		crane->extend(1);
	}
	else {
		crane->extend(0);
	}

}

void GameState::update()
{
	world->Step(1 / 60.f, 8, 3);
	crane->update();
	for (auto& element : game_objects) {
		element->update();
	}
	groundSprite.setPosition(Conversion::metersToPixels(groundBody->GetPosition()));

	scoreText.setString("Score: " + std::to_string(score));
	beamsText.setString("Remaining Beams: " + std::to_string(remainingBeams));
	floorsText.setString("Remaining Floors: " + std::to_string(remainingFloors));
}

void GameState::render(sf::RenderTarget* target)
{
	window->clear(sf::Color(135, 206, 235));

	for (auto& element : game_objects) {
		target->draw(element->getSprite());
	}
	target->draw(crane->getArmSprite());
	target->draw(clawdiusSprite);
	target->draw(craneSprite);
	target->draw(crane->getJointSprite());
	target->draw(groundSprite);
	target->draw(scoreText);
	target->draw(beamsText);
	target->draw(floorsText);
}
