#include "Game.h"

void Game::initWindow()
{
	this->videoMode.height = 1024;
	this->videoMode.width = 1280;
	this->window = new sf::RenderWindow(this->videoMode, "Shooter by Valeriia Yefimova", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
	this->window->setMouseCursorVisible(false);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemy()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initVariables()
{
	this->endGame = false;
	this->maxEnemies = 8;
	this->window = nullptr;
	this->points = 0;
	this->health = 10;
	this->mouseHeld = false;
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Font/Amatic-Bold.ttf")) {
		std::cerr << "ERROR::GAME::INITFONTS::Failed to load font!\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(50);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setOutlineColor(sf::Color::Black);
	this->gameOverText.setOutlineThickness(1);
}

void Game::initTextureBackground()
{
	if (!this->tex.loadFromFile("Textures/back.jpg")) {
		std::cerr << "ERROR::GAME::INITTEXTUREBACKGROUND::Could not load texture file.\n";
	}
}

void Game::initSpriteBackground()
{
	this->sp.setTexture(this->tex);
	this->sp.scale(1.7f, 1.7f);
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initFonts();
	this->initText();
	this->initEnemy();
	this->initTextureBackground();
	this->initSpriteBackground();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	for (auto* i : this->enemies) {
		delete i;
	}
}

void Game::run()
{
	while (running()) {
		this->update();
		this->render();
	}
}

void Game::updatePollEvent()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax && this->enemies.size() < this->maxEnemies) {
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x + 5.f, rand()%this->window->getSize().y+5.f));
		this->spawnTimer = 0.f;
	}

	for (int i = 0; i < enemies.size(); ++i) {
		this->enemies[i]->update();

		if (this->enemies[i]->getBounds().top > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			std::cout << this->enemies.size() << std::endl;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false && mouseCooldown.getElapsedTime().asMilliseconds() >= 100) {
			this->mouseHeld = true;
			bool deleted = false;
			bool hitTarget = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
				if (this->enemies[i]->getBounds().contains(this->mousePosView)) {
					switch (this->enemies[i]->getType()) {
					case 1:
						if (this->enemies[i]->getScaleX() < 0.3f)
							this->points += 2;
						else
							this->points += 1;
						break;
					case 2:
						if (this->enemies[i]->getScaleX() < 0.3f)
							this->points += 3;
						else
							this->points += 2;
						break;
					default:
						this->points += 1;
						break;
					}
					std::cout << "Points: " << this->points << "\n";

					deleted = true;
					hitTarget = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
			if (!hitTarget) {
				this->health -= 1;
				std::cout << "Health: " << this->health << "\n";
			}
			mouseCooldown.restart();
		}
		else {
			this->mouseHeld = false;
		}
	}
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points<<"		\t Health: "<<this->health;
	this->uiText.setString(ss.str());
}

void Game::update()
{
	this->updatePollEvent();
	if (this->endGame == false) {
		this->updateMousePosition();
		this->player->setCrosshairPos(mousePosView);
		this->updateText();
		this->updateEnemies();
	}
	if (this->health <= 0) {
		endGame = true;
		this->restart();
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	this->gameOverText.setString("\tGAME OVER\n\tDo you want to restart? Press R\n\n\n      \tPoints:" + std::to_string(this->points));
	sf::FloatRect textRect = this->gameOverText.getLocalBounds();
	this->gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	this->gameOverText.setPosition(this->window->getSize().x / 2.0f, this->window->getSize().y / 2.0f);
	target.draw(this->uiText);
}

void Game::render()
{
	this->window->clear();
	if (endGame) {
		this->renderBack(*this->window);
		window->draw(gameOverText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
		}
	}
	else {
		this->renderBack(*this->window);

		for (auto* enemy : this->enemies) {
			enemy->render(this->window);
		}
		this->player->render(*this->window);

		this->renderText(*this->window);
	}
	
	this->window->display();
}

void Game::renderBack(sf::RenderTarget& target)
{
	target.draw(this->sp);
}

void Game::restart()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		this->points = 0;
		this->health = 10;
		this->endGame = false;
		this->enemies.clear();
	}
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}