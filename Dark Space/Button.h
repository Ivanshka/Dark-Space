#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Vars.h"

#pragma once

using namespace sf;
using namespace std;

class Button
{
public:
	// ��������������� ����������-������� ��� ������������� ������� ������
	bool Enabled;
	// ����� ������
	RectangleShape Rect;
	// ������� �������� ������� ������. ����������� � ������� ����� ����.
	void Update(Vector2f MousePos, RenderWindow * win);
	// �������, ����������� ��� ������� ������ ����
	void (*Click)(RenderWindow *);
	Button(int x, int y, Texture * background, void (*func)(RenderWindow * win));
	~Button();
};

