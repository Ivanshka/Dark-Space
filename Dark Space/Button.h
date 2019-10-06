#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Vars.h"

#pragma once

using namespace sf;
using namespace std;

class Button
{
public:
	// Вспомогательная переменная-защелка для ЕДИНСТВЕННОГО нажатия кнопки
	bool Enabled;
	// Образ кнопки
	RectangleShape Rect;
	// Функция проверки нажатия кнопки. Вставляется в событие клика мыши.
	void Update(Vector2f MousePos, RenderWindow * win);
	// Функция, выполняемая при нажатии кнопки мыши
	void (*Click)(RenderWindow *);
	Button(int x, int y, Texture * background, void (*func)(RenderWindow * win));
	~Button();
};

