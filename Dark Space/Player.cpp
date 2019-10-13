#include <iostream>
#include <string>

#include "Vars.h"
#include "Player.h"
#include "Bot.h"

Player::Player(int x, int y, string path)
{
	Texture * tPlayer = new Texture();
	tPlayer->loadFromFile(path);
	sprite.setTexture(*tPlayer);
	sprite.setPosition(100, 100);
	sprite.setTextureRect(IntRect(0, 0, 96, 100));
	frame = 0;
	Hp = 100;
}


Player::~Player()
{

}

void Player::Update(Vector2f MousePos, Bot * bots, float time)
{
	sprite.setPosition(MousePos.x - 48, MousePos.y - 50);
	frame += (time * FRAME_MULTIPLIER);
	if (frame > 2)
		frame = 0;
	sprite.setTextureRect(IntRect((int)(frame) * 96, 0, 96, 100));
	for (int i = 0; i < BOT_COUNT; i++)
		if (GetRect().intersects(bots[i].GetRect()))
		{
			Hp -= 20 + rand() % 30;
			KILLED_IN_MISSION++;
			bots[i].ResetBot();
		}
}

FloatRect Player::GetRect()
{
	Vector2f pos = sprite.getPosition();
	return FloatRect(pos.x, pos.y, 96, 100);
}
