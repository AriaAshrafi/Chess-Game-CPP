#include <bits/stdc++.h>
#include <Piece.h>
#include <Setting.h>
#include <SFML/Graphics.hpp>
using namespace std;

void Piece::operator= (Piece &A) {	name = A.name, color = A.color;	}

void Piece::change(char x, char y) {
        name = x, color = y;
        this -> load_texture();
}

void Piece::load_texture() {
        string nc = "";
        nc += name;
        nc += color;
        sf::Texture tmp;
        tmp.loadFromFile("resources/images/" + nc + ".png");
        sp.setTexture(tmp);
        float piece_scale_x = (float)setting::cell_size / sp.getTexture() -> getSize().x;
        float piece_scale_y = (float)setting::cell_size / sp.getTexture() -> getSize().y;
        sp.setScale(piece_scale_x, piece_scale_y);
}
