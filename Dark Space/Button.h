#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
public:
	// ����� ������
	RectangleShape Rect;
	// ������� �������� ������� ������. ����������� � ������� ����� ����.
	void CheckOnClick(Vector2f MousePos);
	// ������� �������� ������� ���� � ������� ��� hover-�������.
	void Update(Vector2f MousePos);
	// �������, ����������� ��� ������� ������ ����
	void (*Click)();
	Button(int x, int y, Texture * background, Texture * hoverBackground, void (*func)());
	~Button();
private:
	Texture* Background;
	Texture* HoverBackground;
};