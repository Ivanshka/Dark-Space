#include <iostream>
#include <string>

#include "Vars.h"
#include "Bullet.h"

using namespace std;

Bullet::Bullet(float x, float y, float speed, Texture * tBullet) {
	X = x; Y = y; Speed = speed;
	sprite.setTexture(*tBullet);
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Update(Bot * bots, float time) {
	for (int i = 0; i < BOT_COUNT; i++)
		if (GetRect().intersects(bots[i].GetRect()))
		{
			bots[i].Hp -= Damage;
			Reset();
			if (bots[i].Hp <= 0)
				bots[i].Reset();
			break;
		}
	sprite.setPosition(X, Y -= time * Speed);
}

FloatRect Bullet::GetRect() {
	return FloatRect(X, Y, 7, 20);
}

void Bullet::Reset() {
	sprite.setPosition(X = -7, Y = 0);
}