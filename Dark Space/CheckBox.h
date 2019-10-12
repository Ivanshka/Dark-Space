#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class CheckBox
{
public:
	// включена?
	bool Enabled;
	// спрайт
	RectangleShape Rect;
	// Функция проверки нажатия кнопки. Вставляется в событие клика мыши.
	void Update(Vector2f MousePos, RenderWindow * win);
	CheckBox(int x, int y, Texture * EnabledBackground, Texture * DisabledBackground, void(*func)(), bool enabled);
	~CheckBox();
private:
	// Вызывается из Update при нажатии на чекбокс
	void Activate();
	// Функция, выполняемая при нажатии кнопки мыши
	void(*Click)();
	// текстура, ставящаяся при деактивации чекбокса
	Texture * DisabledTexture;
	// текстура, ставящаяся при активации чекбокса
	Texture * EnabledTexture;
};

