#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
public:
	// ����� ������
	RectangleShape Rect;
	// ������� �������� ������� ������. ����������� � ������� ����� ����.
	void Update(Vector2f MousePos, RenderWindow * win);
	// �������, ����������� ��� ������� ������ ����
	void (*Click)(RenderWindow *);
	Button(int x, int y, Texture * background, void (*func)(RenderWindow * win));
	~Button();
};