#pragma once

#include <bits/stdc++.h>
using namespace std;

class Piece {
	public:
		char name;
		char color;
		Piece(char x = '-', char y = '-') {	name = x, color = y;	}
		void operator= (Piece &A);
		void change(char x, char y);
};

