#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
public:
	// Образ кнопки
	RectangleShape Rect;
	// Функция проверки нажатия кнопки. Вставляется в событие клика мыши.
	void Update(Vector2f MousePos, RenderWindow * win);
	// Функция, выполняемая при нажатии кнопки мыши
	void (*Click)(RenderWindow *);
	Button(int x, int y, Texture * background, void (*func)(RenderWindow * win));
	~Button();
};