#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
public:
	// Образ кнопки
	RectangleShape Rect;
	// Функция проверки нажатия кнопки. Вставляется в событие клика мыши.
	void CheckOnClick(Vector2f MousePos);
	// Функция проверки встречи мыши с кнопкой для hover-эффекта.
	void Update(Vector2f MousePos);
	// Функция, выполняемая при нажатии кнопки мыши
	void (*Click)();
	Button(int x, int y, Texture * background, Texture * hoverBackground, void (*func)());
	~Button();
private:
	Texture* Background;
	Texture* HoverBackground;
};