#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class CheckBox
{
public:
	// ��������?
	bool Enabled;
	// ������
	RectangleShape Rect;
	// ������� �������� ������� ������. ����������� � ������� ����� ����.
	void Update(Vector2f MousePos, RenderWindow * win);
	CheckBox(int x, int y, Texture * EnabledBackground, Texture * DisabledBackground, void(*func)(), bool enabled);
	~CheckBox();
private:
	// ���������� �� Update ��� ������� �� �������
	void Activate();
	// �������, ����������� ��� ������� ������ ����
	void(*Click)();
	// ��������, ���������� ��� ����������� ��������
	Texture * DisabledTexture;
	// ��������, ���������� ��� ��������� ��������
	Texture * EnabledTexture;
};

