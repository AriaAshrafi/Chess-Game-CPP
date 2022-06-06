#include <bits/stdc++.h>
#include <Piece.h>
#include <Setting.h>
#include <SFML/Graphics.hpp>
using namespace std;

map <string, sf::Texture> mp;

void Piece::operator= (Piece &A) {	name = A.name, color = A.color;	}

void Piece::change(char x, char y) {
        name = x, color = y;
}

void Piece::load_texture() {
        string nc = "";
        nc += name;
        nc += color;
        if (mp.find(nc) == mp.end())
                mp[nc].loadFromFile("resources/images/" + nc + ".png");
        this -> sp.setTexture(mp[nc]);
        float piece_scale_x = (float)setting::cell_size / sp.getTexture() -> getSize().x;
        float piece_scale_y = (float)setting::cell_size / sp.getTexture() -> getSize().y;
        this -> sp.setScale(piece_scale_x, piece_scale_y);
        this -> sp.setPosition(rect.getPosition());
}
