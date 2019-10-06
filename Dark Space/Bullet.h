#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Bot.h"

using namespace sf;
using namespace std;

class Bullet
{
public:
	unsigned char Damage;
	float X, Y, Speed;
	Sprite sprite;
	Bullet(float x, float y, float speed, Texture * tBullet);
	Bullet();
	~Bullet();
	void Update(Bot * bots, float time);
	FloatRect GetRect();
};
