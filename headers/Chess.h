#pragma once

#include <bits/stdc++.h>
#include <Piece.h>
#include <SFML/Graphics.hpp>
#include <Setting.h>
using namespace std;

class Chess {
        public:
                Chess(sf::RenderWindow* _window);
                Piece board[12][12];
                bool isfin = false, oneClick = false;
                pair<int, int> lastClick = pair<int, int>(0, 0);
                char turn = 'W';
                sf::RenderWindow* window;
                sf::Font font;
                sf::Text stat;
                sf::Text res;
                sf::Text inp;

                void init();
                void input();
                void res_col();
                void mouse_clicked(const sf::Vector2i& pos);
                void draw();
                void stat_upd();
                bool danger(int r1, int c1, int r2, int c2);
                bool ischeck(char y);
                bool ismate(char y);
                bool rmove(int r1, int c1, int r2, int c2, int x, int y);
                void move(string s);
                void run();
};
