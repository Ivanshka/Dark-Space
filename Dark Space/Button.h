#include "Vars.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#pragma once

using namespace sf;

class Button
{
public:
	bool Enabled; // ����������� ������
	Vector2i Width; // ������
	Vector2i Height; // ������
	Vector2i Coord; // ����������
	Sprite Background;
	void Update(Vector2f MousePos);
	Button();
	~Button();
};

