#include "CheckBox.h"



CheckBox::CheckBox(int x, int y, Texture * EnabledBackground, Texture * DisabledBackground, void(*func)())
{
	DisabledTexture = DisabledBackground;
	EnabledTexture = EnabledBackground;
	Rect.setPosition(Vector2f(x, y));
	Rect.setSize(Vector2f(50, 50));
	if (Enabled)
		Rect.setTexture(DisabledTexture);
	else
		Rect.setTexture(EnabledTexture);
	Click = func;
}


CheckBox::~CheckBox()
{
}

// ������: 50 � 50
void CheckBox::Update(Vector2f MousePos, RenderWindow * win)
{
	Vector2f rect = Rect.getPosition();
	if (MousePos.x > rect.x && MousePos.x < rect.x + 50)
		if (MousePos.y > rect.y && MousePos.y < rect.y + 50)
			Activate();
}

// ������� ��� ��������� ���������� ������� ��������. �� ����� �� ��� ����� ��������� � Update, ������ ��� ����������
void CheckBox::Activate()
{
	Enabled = !Enabled;
	if (Enabled)
		Rect.setTexture(DisabledTexture);
	else
		Rect.setTexture(EnabledTexture);
	Click();
}