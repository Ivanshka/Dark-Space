#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class CheckBox
{
public:
	// ������
	RectangleShape Rect;
	// ������� �������� ������� ������. ����������� � ������� ����� ����.
	void Update(Vector2f MousePos);
	CheckBox(int x, int y, Texture * EnabledBackground, Texture * DisabledBackground, void(*func)(), bool enabled);
	~CheckBox();
private:
	// ��������?
	bool Enabled;
	// �������, ����������� ��� ������� ������ ����
	void(*Click)();
	// ��������, ���������� ��� ����������� ��������
	Texture * DisabledTexture;
	// ��������, ���������� ��� ��������� ��������
	Texture * EnabledTexture;
};

