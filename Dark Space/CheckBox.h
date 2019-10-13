#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class CheckBox
{
public:
	// спрайт
	RectangleShape Rect;
	// Функция проверки нажатия кнопки. Вставляется в событие клика мыши.
	void Update(Vector2f MousePos);
	CheckBox(int x, int y, Texture * EnabledBackground, Texture * DisabledBackground, void(*func)(), bool enabled);
	~CheckBox();
private:
	// включена?
	bool Enabled;
	// Функция, выполняемая при нажатии кнопки мыши
	void(*Click)();
	// текстура, ставящаяся при деактивации чекбокса
	Texture * DisabledTexture;
	// текстура, ставящаяся при активации чекбокса
	Texture * EnabledTexture;
};

