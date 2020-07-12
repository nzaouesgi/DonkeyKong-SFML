#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "Entity.h"
#include "Level.h"

#define FONT_PATH "Media/Sansation.ttf"

const unsigned int Game::windowWidth = 1920;
const unsigned int Game::windowHeight = 1080;

const sf::Time Game::frameTime = sf::seconds(1.f / 60.f);

Game::Game(): renderWindow(sf::VideoMode(Game::windowWidth, Game::windowHeight), "Donkey Kong 1981", sf::Style::Close) {

	this->renderWindow.setFramerateLimit(160);
	this->renderWindow.display();

	std::vector<std::string> map;
	map.push_back("################################################################################");
	map.push_back("#................oooo...oooo........................................ooooo......#");
	map.push_back("#.........###....oooo...................ooooo........ooooo..........#####..#####");
	map.push_back("#p......#####....######.................ooooo........ooooo......#########..#####");
	map.push_back("####.###########################o####................####################..#####");
	map.push_back("#..............................#o####...............####.............####..#####");
	map.push_back("#oooooo........................#oooo..............######.............####..#####");
	map.push_back("#oooooo.......oooo.............#oooo.............#######.............####..#####");
	map.push_back("###########...####.............#########################...................#####");
	map.push_back("#.............######..........oooooo.........................oooooo........#####");
	map.push_back("#.............##########......######.........................oooooo........#####");
	map.push_back("#.....oooo.................############...##....##...........oooooo........#####");
	map.push_back("##....#######################################..#################################");
	map.push_back("##.............................................................................#");
	map.push_back("######..........ooooo..........................................oooooo..........#");
	map.push_back("########........ooooo..............########################....oooooo.........e#");
	map.push_back("###############################..#########.........#############################");
	map.push_back("................................................................................");

	this->level = std::make_unique<Level>(map);

	// get entities from initial level setup
	std::vector< std::shared_ptr<Entity>> entities = level->create();

	for (std::shared_ptr<Entity> entity : entities) {
		switch (entity->type) {
			case EntityType::PLAYER:
				this->mario = std::dynamic_pointer_cast<Mario>(entity);
				break;
			case EntityType::BLOCK:
				this->blocks.push_back(std::dynamic_pointer_cast<Block>(entity));
				break;
			case EntityType::COIN:
				this->coins.push_back(std::dynamic_pointer_cast<Coin>(entity));
				break;
		}
	}

	this->camera = std::make_unique<Camera>(this->renderWindow.getView());

	if (this->mario == nullptr)
		throw new std::runtime_error("Player was not found in level.");

	if (this->font.loadFromFile(FONT_PATH) == false) {
		throw new std::runtime_error("Could not load stats font.");
	}

	this->stats.setCharacterSize(20);
	this->stats.setFont(this->font);
}

Game::~Game(){}

void Game::run() {

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->renderWindow.isOpen()){
		
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > Game::frameTime){
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

	// Update mario movements
	this->updatePlayer(elapsedTime);

	// Update camera position
	this->updateCamera();

	// Update stats
	this->updateStatistics();
}

void Game::updatePlayer(sf::Time elapsedTime) {
	
	// Update mario movements
	if (mIsMovingLeft) {
		this->mario->moveLeft();
	}

	if (mIsMovingRight) {
		this->mario->moveRight();
	}

	if (!mIsMovingLeft && !mIsMovingRight || mIsMovingLeft && mIsMovingRight) {
		this->mario->stop();
	}

	if (mIsJumping) {
		this->mario->jump();
	}

	this->mario->updateState();
	this->mario->updatePosition(elapsedTime, this->blocks);
	this->mario->pickCoin(this->coins);
}

void Game::updateCamera() {

	sf::Vector2f mapDimensions((float)this->level->mapPixelsWidth, (float)this->level->mapPixelsHeight);
	
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
	this->stats.setString(statsString);

	this->stats.setPosition(5.f + (this->renderWindow.getView().getCenter().x - (Game::windowWidth / 2)) , this->level->mapPixelsHeight - (this->level->baseEntitySize));
}

void Game::render(){
	this->renderWindow.clear();

	// draw blocks
	for (std::shared_ptr<Block> block : this->blocks)
		this->renderWindow.draw(block->sprite);

	// draw player
	this->renderWindow.draw(mario->sprite);

	// draw coins
	for (std::shared_ptr<Coin> coin : this->coins) {
		if (!coin->isPickedUp()) {
			this->renderWindow.draw(coin->sprite);
		}
	}

	this->renderWindow.draw(this->stats);

	this->renderWindow.display();
}
	
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
	if (key == sf::Keyboard::Left)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		mIsMovingRight = isPressed;

	if (key == sf::Keyboard::Space){
		mIsJumping = isPressed;
	}
}