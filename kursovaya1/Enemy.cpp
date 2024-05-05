#include "Enemy.h"
#include "Player.h"
void Enemy::initSpriteEnemy()
{
	this->sp.setTexture(this->tex);
}

void Enemy::initTextureEnemy()
{
	this->type = rand() % 3;
	switch (type) {
	case 0:
		this->tex.loadFromFile("Textures/rubber-duck-target.png");{
		float scale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (0.5f - 0.3f) + 0.1f;
		this->sp.scale(scale, scale);
		}
		break;
	case 1:
		this->tex.loadFromFile("Textures/target-red.png"); {
			float scale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (0.4f - 0.1f) + 0.1f;
			this->sp.scale(scale, scale);
		}
		break;
	default:
		this->tex.loadFromFile("Textures/duck-target-yellow.png");
		this->sp.scale(0.4f, 0.4f);
		break;
	}
}

void Enemy::initVariables()
{
	this-> type			= 0;
	this->xstep			= 3;
	this->ystep			= 3;

	float minSpeed = 0.2f;
	float maxSpeed = 1.0f;
	this-> speed = minSpeed + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxSpeed - minSpeed)));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initTextureEnemy();
	this->initSpriteEnemy();
	this->initVariables();

	this->sp.setPosition(sf::Vector2f(pos_x, pos_y));
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->sp.getGlobalBounds();
}

void Enemy::update()
{
	this->sp.move(xstep, ystep);

	float enemyWidth = sp.getLocalBounds().width/2;
	float enemyHeight = sp.getLocalBounds().height / 3;

	switch (this->sp.getPosition().x + enemyWidth > 1280 ? 1 : this->sp.getPosition().x < 0 ? 2 : 0) {
	case 1:
		this->xstep = -3;
		break;
	case 2:
		this->xstep = 3;
		break;
	}

	switch (this->sp.getPosition().y + enemyHeight > 1024 ? 1 : this->sp.getPosition().y < 0 ? 2 : 0) {
	case 1:
		this->ystep = -3;
		break;
	case 2:
		this->ystep = 3;
		break;
	}
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sp);
}

float Enemy::getPositionX() const
{
	return this->sp.getPosition().x;
}

float Enemy::getPositionY() const
{
	return this->sp.getPosition().y;
}
int Enemy::getType() const
{
	return this->type;
}
float Enemy::getScaleX() const
{
	float scaleFloat = sp.getScale().x;
	return scaleFloat;
}