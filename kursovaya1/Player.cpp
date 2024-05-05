#include "Player.h"

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.4f, 0.4f);
	this->sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Textures/crosshair1.png")) {
		std::cerr << "ERROR::PLAYER::INITTEXTURE::Could not load texture file.\n";
	}
}

Player::Player()
{
	this->movementSpeed = 10.f;
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::setCrosshairPos(const sf::Vector2f crossPos)
{
	this->sprite.setPosition(crossPos);
}
