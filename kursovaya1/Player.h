#pragma once
#include<iostream>
#include<sstream>
#include<vector>
#include<time.h>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>
#include<SFML/Audio.hpp>
#include"Enemy.h"
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	void initSprite();
	void initTexture();

public:
	Player();
	virtual ~Player();

	void move(const float dirX, const float dirY);
	void render(sf::RenderTarget&target);

	void setCrosshairPos(const sf::Vector2f crossPos);
};