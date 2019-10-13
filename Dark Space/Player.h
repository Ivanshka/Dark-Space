#pragma once
#include <string>

#include <SFML/Graphics.hpp>

#include "Bot.h"

using namespace sf;
using namespace std;

class Player
{
public:
	Sprite sprite;
	Player(int x, int y, string pathToTexture);
	~Player();
	void Update(Vector2f MousePos, Bot * bots, float time);
	FloatRect GetRect();
	float frame;
	int Hp;
};

