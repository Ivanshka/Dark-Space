#pragma once
#include <string>

#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class Bot
{
public:
	short MaxHp;
	short Hp;
	Sprite sprite;
	float X, Y, Speed;
	Bot();
	Bot(float x, float y, float speed, float maxHp, Texture * tBot);
	~Bot();
	void Update(float time);
	void ResetBot();
	FloatRect GetRect();
	float frame;
};
