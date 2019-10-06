#include "Button.h"


// размеры: 180 х 50
Button::Button(int x, int y, Texture * background, void (*func)(RenderWindow * win))
{
	Enabled = true;
	Rect.setPosition(x, y);
	Rect.setTexture(background);
	Rect.setSize(Vector2f(180, 50));
	Click = func;
}

Button::~Button()
{
}

void Button::Update(Vector2f MousePos, RenderWindow * win)
{
	Vector2f rect = Rect.getPosition();
	if (MousePos.x > rect.x && MousePos.x < rect.x + 180)
		if (MousePos.y > rect.y && MousePos.y < rect.y + 50)
			Click(win);
}