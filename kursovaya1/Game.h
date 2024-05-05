#pragma once
#include"Player.h"
#include"Enemy.h"
class Game
{
private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text uiText;
	sf::Text gameOverText;
	sf::Sprite sp;
	sf::Texture tex;

	Player* player;

	float spawnTimer;
	float spawnTimerMax;
	int maxEnemies;
	std::vector<Enemy*> enemies;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	sf::VideoMode videoMode;
	sf::Clock mouseCooldown;

	unsigned points;
	int health;
	bool mouseHeld;
	bool endGame;

	void initWindow();
	void initPlayer();
	void initEnemy();
	void initVariables();
	void initFonts();
	void initText();
	void initTextureBackground();
	void initSpriteBackground();
public:
	Game();
	virtual ~Game();

	void run();
	void restart();

	void updatePollEvent();
	void updateEnemies();
	void updateMousePosition();
	void updateText();
	void update();

	void renderText(sf::RenderTarget& target);
	void render();
	void renderBack(sf::RenderTarget& target);

	const bool running() const;
	const bool getEndGame()const;
};

