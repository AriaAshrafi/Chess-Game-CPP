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

void Piece::load_texture(int fl) {
        if (fl) {
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
        else {

                //green and red dots
                if (mp.find("DG") == mp.end())
                        mp["DG"].loadFromFile("resources/images/DG.png");
                if (mp.find("DR") == mp.end())
                        mp["DR"].loadFromFile("resources/images/DR.png");

                this -> spDG.setTexture(mp["DG"]);
                float piece_scale_x = (float)setting::cell_size / spDG.getTexture() -> getSize().x;
                float piece_scale_y = (float)setting::cell_size / spDG.getTexture() -> getSize().y;
                this -> spDG.setScale(piece_scale_x, piece_scale_y);
                this -> spDG.setPosition(rect.getPosition());
                
                this -> spDR.setTexture(mp["DR"]);
                float piece_scale_x2 = (float)setting::cell_size / spDR.getTexture() -> getSize().x;
                float piece_scale_y2 = (float)setting::cell_size / spDR.getTexture() -> getSize().y;
                this -> spDR.setScale(piece_scale_x2, piece_scale_y2);
                this -> spDR.setPosition(rect.getPosition());
        }
}
