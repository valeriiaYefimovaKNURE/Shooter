#ifndef ENEMY_H
#define ENEMY_H
#include"Player.h"
class Enemy
{
private:
	sf::Sprite sp;
	sf::Texture tex;

	int type;
	float speed;
	float xstep;
	float ystep;

	void initSpriteEnemy();
	void initTextureEnemy();
	void initVariables();
public:
	Enemy(float pos_x,float pos_y);
	virtual ~Enemy();

	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);

	float getPositionX()const;
	float getPositionY()const;
	int getType()const;
	float getScaleX()const;
};

#endif ENEMY_H