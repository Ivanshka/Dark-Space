#include "CheckBox.h"



CheckBox::CheckBox(int x, int y, Texture * EnabledBackground, Texture * DisabledBackground, void(*func)(), bool enabled)
{
	DisabledTexture = DisabledBackground;
	EnabledTexture = EnabledBackground;
	Rect.setPosition(Vector2f(x, y));
	Rect.setSize(Vector2f(50, 50));
	Enabled = enabled;
	if (Enabled)
		Rect.setTexture(EnabledTexture);
	else
		Rect.setTexture(DisabledTexture);
	Click = func;
}


CheckBox::~CheckBox()
{
}

// размер: 50 х 50
void CheckBox::CheckOnClick(Vector2f MousePos)
{
	Vector2f rect = Rect.getPosition();
	if (MousePos.x > rect.x && MousePos.x < rect.x + 50)
		if (MousePos.y > rect.y&& MousePos.y < rect.y + 50)
		{
			Enabled = !Enabled;
			if (Enabled)
				Rect.setTexture(EnabledTexture);
			else
				Rect.setTexture(DisabledTexture);
			if (Click != NULL) Click();
		}
}