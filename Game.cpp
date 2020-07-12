#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "Entity.h"
#include "Level.h"

#define FONT_PATH "Media/Sansation.ttf"

const unsigned int Game::windowWidth = 1920;
const unsigned int Game::windowHeight = 1080;

const sf::Time Game::frameTime = sf::seconds(1.f / 60.f);

Game::Game(std::vector<std::vector<std::string>> maps):
	
	renderWindow(sf::VideoMode(Game::windowWidth, Game::windowHeight), "Donkey Kong 1981", sf::Style::Close) {

	this->maps = maps;

	this->renderWindow.setFramerateLimit(160);
	this->renderWindow.display();

	if (this->font.loadFromFile(FONT_PATH) == false) {
		throw new std::runtime_error("Could not load stats font.");
	}

	this->init();

	this->customizeStatText();
	this->customizeGameFinishedText();

	this->camera = std::make_unique<Camera>(this->renderWindow.getView());

	this->allGamesDone = false;
}

void Game::init() {
	
	this->gameOver = false;
	this->gameWon = false;

	this->isJumping = false;
	this->isMovingLeft = false;
	this->isMovingRight = false;
	this->isRestart = false;
	this->isNextLevel = false;

	this->mario = nullptr;
	this->mario = nullptr;
	this->blocks = {};
	this->monsters = {};
	this->coins = {};
}

Game::~Game(){}

void Game::run(size_t mapIndex) {

	this->currentMap = mapIndex;

	this->init();

	this->level = std::make_unique<Level>(this->maps[mapIndex]);

	// get entities from initial level setup
	std::vector< std::shared_ptr<Entity>> entities = level->create();

	for (std::shared_ptr<Entity> entity : entities) {
		switch (entity->type) {
		
			case EntityType::PLAYER:
				this->mario = std::dynamic_pointer_cast<Mario>(entity);
				break;

			case EntityType::PRINCESS:
				this->princess = std::dynamic_pointer_cast<Princess>(entity);
				break;

			case EntityType::BLOCK:
				this->blocks.push_back(std::dynamic_pointer_cast<Block>(entity));
				break;

			case EntityType::COIN:
				this->coins.push_back(std::dynamic_pointer_cast<Coin>(entity));
				break;

			case EntityType::MONSTER:
				this->monsters.push_back(std::dynamic_pointer_cast<Monster>(entity));
				break;
		}
	}

	if (this->mario == nullptr)
		throw new std::runtime_error("Player was not found in level.");

	if (this->princess == nullptr)
		throw new std::runtime_error("Princess was not found in level.");

	this->mainLoop();
}

void Game::mainLoop() {
	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->renderWindow.isOpen()) {

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > Game::frameTime) {
			timeSinceLastUpdate -= Game::frameTime;
			processEvents();
			update(Game::frameTime);
		}

		render();
		sf::sleep(sf::microseconds(1));
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (this->renderWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			this->renderWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime){

	if (this->gameWon == true && this->currentMap == this->maps.size() - 1) {
		this->allGamesDone = true;
	}

	if (this->isRestart) {
		this->run(this->currentMap);
		return;
	}

	if (this->isNextLevel && this->gameWon == true && this->allGamesDone != true) {
		this->run(this->currentMap + 1);
		return;
	}

	this->updateGameFinishedText();

	if (this->gameOver == true || this->gameWon == true) {
		return;
	}

	// Update mario movements
	this->updatePlayer(elapsedTime);

	// Update camera position
	this->updateCamera();

	// Update stats
	this->updateStatistics();

	// Update monsters
	this->updateMonsters(elapsedTime);

	// Update princess
	this->updatePrincess();
}

void Game::updateMonsters(sf::Time elapsedTime) {
	for (std::shared_ptr<Monster> monster : this->monsters) {
		
		monster->updatePosition(elapsedTime, this->blocks);
		
		if (monster->killMario(this->mario) == true) {
			this->gameOver = true;
		}
	}
}

void Game::updatePlayer(sf::Time elapsedTime) {
	
	// Update mario movements
	if (isMovingLeft) {
		this->mario->moveLeft();
	}

	if (isMovingRight) {
		this->mario->moveRight();
	}

	if (!isMovingLeft && !isMovingRight || isMovingLeft && isMovingRight) {
		this->mario->stop();
	}

	if (isJumping) {
		this->mario->jump();
	}

	if (this->mario->hasFallen(this->level->mapRect)) {
		this->gameOver = true;
	}

	this->mario->updateState();
	this->mario->updatePosition(elapsedTime, this->blocks);
	this->mario->pickCoin(this->coins);
	this->mario->savePrincess(this->princess);
}

void Game::updatePrincess() {
	if (this->princess->isSaved() == true) {
		this->gameWon = true;
	}
}

void Game::updateCamera() {

	sf::Vector2f mapDimensions((float)this->level->mapRect.width, (float)this->level->mapRect.height);
	
	this->renderWindow.setView(
		this->camera->updatePosition(
			mapDimensions, 
			this->mario->sprite.getPosition().x + (this->mario->sideLength / 2)
		));
}

void Game::updateStatistics(){
	
	unsigned coinsPickedUp = 0;
	for (std::shared_ptr<Coin> coin : coins) {
		if (coin->isPickedUp()) {
			coinsPickedUp++;
		}
	}
	std::string statsString = "Coins: " + std::to_string(coinsPickedUp);
	this->statsText.setString(statsString);

	this->statsText.setPosition(
		5.f + (this->renderWindow.getView().getCenter().x - (Game::windowWidth / 2)), 
		this->level->mapRect.height - (this->level->baseEntitySize));
}

void Game::updateGameFinishedText() {
	this->gameFinishedText.setPosition(
		(this->renderWindow.getView().getCenter().x) - (this->gameFinishedText.getLocalBounds().width / 2), 
		this->level->mapRect.height / 2);
}

void Game::render(){
	
	this->renderWindow.clear();

	// draw blocks
	for (std::shared_ptr<Block> block : this->blocks)
		this->renderWindow.draw(block->sprite);

	// draw coins
	for (std::shared_ptr<Coin> coin : this->coins) 
		if (!coin->isPickedUp()) 
			this->renderWindow.draw(coin->sprite);
		
	// draw monsters
	for (std::shared_ptr<Monster> monster : this->monsters) 
		this->renderWindow.draw(monster->sprite);

	// draw stats
	this->renderWindow.draw(this->statsText);

	// draw player
	this->renderWindow.draw(mario->sprite);

	// draw princess
	this->renderWindow.draw(princess->sprite);

	if (this->gameOver) {
		this->gameFinishedText.setString("Game over (R to restart).");
		this->renderWindow.draw(this->gameFinishedText);
	}

	if (this->gameWon && this->allGamesDone == false) {
		this->gameFinishedText.setString("You won ! (N for next level)");
		this->renderWindow.draw(this->gameFinishedText);
	}

	if (this->gameWon && this->allGamesDone == true) {
		this->gameFinishedText.setString("You are the champion, my friend. Bye bye !");
		this->renderWindow.draw(this->gameFinishedText);
	}

	this->renderWindow.display();
}
	
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
	if (key == sf::Keyboard::Left)
		isMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		isMovingRight = isPressed;

	if (key == sf::Keyboard::Space){
		isJumping = isPressed;
	}

	if (key == sf::Keyboard::R) {
		this->isRestart = isPressed;
	}

	if (key == sf::Keyboard::N) {
		this->isNextLevel = isPressed;
	}
}

void Game::customizeStatText() {

	this->statsText.setCharacterSize(20);
	this->statsText.setFont(this->font);
}

void Game::customizeGameFinishedText() {
	sf::Color gameOverColor;
	gameOverColor.r = 222;
	gameOverColor.g = 222;
	gameOverColor.b = 0;

	this->gameFinishedText.setFont(this->font);
	this->gameFinishedText.setFillColor(gameOverColor);
	this->gameFinishedText.setCharacterSize(80);
}