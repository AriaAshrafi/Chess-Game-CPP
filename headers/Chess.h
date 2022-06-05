#pragma once

#include <bits/stdc++.h>
#include <Piece.h>
using namespace std;

class Chess {
        public:
                Piece board[12][12];
                char turn = 'W';
                Chess() {
                        //Pawns
                        for (int i = 1; i < 9; i++)
                                board[2][i].change('P', 'B'),
                                        board[7][i].change('P', 'W');

                        //Rooks
                        board[1][1].change('R', 'B');
                        board[1][8].change('R', 'B');
                        board[8][1].change('R', 'W');
                        board[8][8].change('R', 'W');

                        //Knights
                        board[1][2].change('N', 'B');
                        board[1][7].change('N', 'B');
                        board[8][2].change('N', 'W');
                        board[8][7].change('N', 'W');

                        //Bishops
                        board[1][3].change('B', 'B');
                        board[1][6].change('B', 'B');
                        board[8][3].change('B', 'W');
                        board[8][6].change('B', 'W');

                        //Queens
                        board[1][4].change('Q', 'B');
                        board[8][4].change('Q', 'W');

                        //Kings
                        board[1][5].change('K', 'B');
                        board[8][5].change('K', 'W');
                }
                bool danger(int r1, int c1, int r2, int c2);
                bool ischeck(char y);
                bool ismate(char y);
                bool rmove(int r1, int c1, int r2, int c2, int x, int y);
                void move(string s);
};
