#include "Vars.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#pragma once

using namespace sf;

class Button
{
public:
	bool Enabled; // доступность кнопки
	Vector2i Width; // ширина
	Vector2i Height; // высота
	Vector2i Coord; // координаты
	Sprite Background;
	void Update(Vector2f MousePos);
	Button();
	~Button();
};

