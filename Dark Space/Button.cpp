#include "Button.h"


// �������: 180 � 50
Button::Button(int x, int y, Texture * background, Texture * hoverBackground, void (*func)()) {
	Rect.setPosition(x, y);
	Rect.setTexture(background);
	Rect.setSize(Vector2f(180, 50));
	Background = background;
	HoverBackground = hoverBackground;
	Click = func;
}

Button::~Button() {
}

void Button::CheckOnClick(Vector2f MousePos) {
	Vector2f rect = Rect.getPosition();
	if (MousePos.x > rect.x && MousePos.x < rect.x + 180)
		if (MousePos.y > rect.y && MousePos.y < rect.y + 50)
			Click();
}

void Button::Update(Vector2f MousePos) {
	Vector2f rect = Rect.getPosition();
	Rect.setTexture(Background);
	if (MousePos.x > rect.x&& MousePos.x < rect.x + 180)
		if (MousePos.y > rect.y&& MousePos.y < rect.y + 50)
			Rect.setTexture(HoverBackground);
}