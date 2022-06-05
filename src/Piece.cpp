#include <bits/stdc++.h>
#include <Piece.h>
using namespace std;

void Piece::operator= (Piece &A) {	name = A.name, color = A.color;	}
void Piece::change(char x, char y) {	name = x, color = y;	}
