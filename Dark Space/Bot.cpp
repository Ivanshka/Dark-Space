#include <iostream>

#include <SFML/Graphics.hpp>

#include "Bot.h"
#include "Vars.h"

using namespace sf;

Bot::Bot(float x, float y, float speed, float maxHp, Texture * tBot)
{
	sprite.setTexture(*tBot);
	X = x; Y = y; Speed = speed; MaxHp = maxHp; Hp = maxHp;
	sprite.setPosition(X, Y);
	sprite.setTextureRect(IntRect(0, 0, BOT_WIDTH, BOT_HEIGHT));
	frame = 0;
}

Bot::Bot()
{
}


Bot::~Bot()
{
}

void Bot::Update(float time)
{
	if (Y > 600)
		ResetBot();
	else
		sprite.setPosition(X, Y += time*Speed);
	frame += (time * FRAME_MULTIPLIER);
	if (frame > 2)
		frame = 0;
	sprite.setTextureRect(IntRect((int)(frame) * BOT_WIDTH, 0, BOT_WIDTH, BOT_HEIGHT));
}

void Bot::ResetBot()
{
	Hp = MaxHp;
	sprite.setPosition(X = rand() % 704, Y = -(BOT_HEIGHT + rand() % 768));
}

FloatRect Bot::GetRect()
{
	return FloatRect(X, Y, BOT_WIDTH, BOT_HEIGHT);
}