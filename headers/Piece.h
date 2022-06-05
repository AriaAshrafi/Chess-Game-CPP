#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Setting.h>
using namespace std;

class Piece {
	public:
		char name;
		char color;
                sf::RectangleShape rect;
                sf::Sprite sp;

		Piece(char x = '-', char y = '-') {	name = x, color = y;	}
                void load_texture();
		void operator= (Piece &A);
		void change(char x, char y);
};

