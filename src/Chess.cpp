#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Chess.h>
#include <Setting.h>
#include <Others.h>
using namespace std;

Chess::Chess(sf::RenderWindow* _window) : window(_window) {     this -> window -> setFramerateLimit(60);      }

void Chess::init() {
        for (int i = 1; i < 9; i++)
                for (int j = 1; j < 9; j++) {
                        board[i][j].rect.setSize(sf::Vector2f(setting::cell_size, setting::cell_size));
                        board[i][j].rect.setFillColor(setting::cell_color);
                        board[i][j].rect.setPosition(get_pos(i, j));
                }

        font.loadFromFile("resources/fonts/arial.TTF");
        stat.setFont(font);
        stat.setCharacterSize(30);
        stat.setStyle(sf::Text::Regular);
        stat.setFillColor(sf::Color::Black);
        stat.setPosition(400.f, 80.f);
        stat.setString("White turns");

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

bool Chess::danger(int r1, int c1, int r2, int c2) { //Check if the piece in [r2][c2] is in danger by [r1][c1]

        char na = board[r1][c1].name, col = board[r1][c1].color;

        //Pawn
        if (na == 'P') {
                if (abs(c1 - c2) == 1 and ((r2 == r1 + 1 and col == 'B') or (r2 == r1 - 1 and col == 'W')))
                        return true;
        }

        //Rook
        if (na == 'R') {
                if (c1 == c2) {
                        bool flag = true;
                        for (int i = min(r1, r2) + 1; i < max(r1, r2); i++)
                                if (board[i][c1].name != '-')
                                        flag = false;
                        if (flag)
                                return true;
                }
                if (r1 == r2) {
                        bool flag = true;
                        for (int i = min(c1, c2) + 1; i < max(c1, c2); i++)
                                if (board[r1][i].name != '-')
                                        flag = false;
                        if (flag)
                                return true;
                }
        }

        //Knight
        if (na == 'N') {
                if ((abs(r2 - r1) == 1 and abs(c2 - c1) == 2) or (abs(r2 - r1) == 2 and abs(c2 - c1) == 1))
                        return true;
        }

        //Bishop
        if (na == 'B') {
                bool flag = true;
                if (abs(c2 - c1) != abs(r2 - r1))
                        flag = false;
                int s1 = (r2 > r1? 1: -1),
                    s2 = (c2 > c1? 1: -1);
                for (int i = 1; i < abs(r2 - r1) and flag; i++)
                        if (board[r1 + s1 * i][c1 + s2 * i].name != '-')
                                flag = false;
                if (flag)
                        return true;

        }

        //Queen
        if (na == 'Q') {
                //A queen can move like a bishop and a rook so we consider both cases
                //Rook
                if (c1 == c2) {
                        bool flag = true;
                        for (int i = min(r1, r2) + 1; i < max(r1, r2); i++)
                                if (board[i][c1].name != '-')
                                        flag = false;
                        if (flag)
                                return true;
                }
                if (r1 == r2) {
                        bool flag = true;
                        for (int i = min(c1, c2) + 1; i < max(c1, c2); i++)
                                if (board[r1][i].name != '-')
                                        flag = false;
                        if (flag)
                                return true;
                }
                //Bishop
                bool flag = true;
                if (abs(c2 - c1) != abs(r2 - r1))
                        flag = false;
                int s1 = (r2 > r1? 1: -1),
                    s2 = (c2 > c1? 1: -1);
                for (int i = 1; i < abs(r2 - r1) and flag; i++)
                        if (board[r1 + s1 * i][c1 + s2 * i].name != '-')
                                flag = false;
                if (flag)
                        return true;
        }

        //King
        if (na == 'K') {
                if (abs(r2 - r1) < 2 and abs(c2 - c1) < 2)
                        return true;
        }

        return false;
}

bool Chess::ischeck(char y) {
        //Locating the king
        int r, c;
        for (int i = 1; i < 9; i++)
                for (int j = 1; j < 9; j++)
                        if (board[i][j].name == 'K' and board[i][j].color == y)
                                r = i, c = j;

        //Check if a piece is in dangering the king
        for (int i = 1; i < 9; i++)
                for (int j = 1; j < 9; j++)
                        if (board[i][j].color != '-' and board[i][j].color != y and danger(i, j, r, c))
                                return true;
        return false;
}

bool Chess::ismate(char y) {
        //If the player with color y has a right move then he isn't mate

        for (int i = 1; i < 9; i++)
                for (int j = 1; j < 9; j++) {
                        if (board[i][j].color != y)
                                continue;
                        for (int k = 1; k < 9; k++)
                                for (int p = 1; p < 9; p++)
                                        if (rmove(i, j, k, p, board[i][j].name, board[i][j].color))
                                                return false;
                }
        return true;
}

bool Chess::rmove(int r1, int c1, int r2, int c2, int x, int y) {

        //Some basic rules
        if (r1 == r2 and c1 == c2)
                return false;
        if (r1 < 1 or r1 > 8 or c1 < 1 or c1 > 8)
                return false;
        if (r2 < 1 or r2 > 8 or c2 < 1 or c2 > 8)
                return false;
        if (board[r1][c1].name != x or board[r1][c1].color != y)
                return false;
        if (board[r2][c2].color == y)
                return false;

        //Pawn
        if (x == 'P') {
                if (c1 == c2 and ((r2 == r1 + 1 and y == 'B') or (r2 == r1 - 1 and y == 'W'))) {
                        if (board[r2][c2].name != '-')
                                return false;
                }
                else if (abs(c1 - c2) == 1 and ((r2 == r1 + 1 and y == 'B') or (r2 == r1 - 1 and y == 'W'))) {
                        if (board[r2][c2].name == '-' or board[r2][c2].color == y)
                                return false;
                }
                else
                        return false;
        }

        //Rook
        if (x == 'R') {
                if (r1 != r2 and c1 != c2)
                        return false;
                if (r1 == r2) {
                        for (int i = min(c1, c2) + 1; i < max(c1, c2); i++)
                                if (board[r1][i].name != '-')
                                        return false;
                }
                else {
                        for (int i = min(r1, r2) + 1; i < max(r1, r2); i++)
                                if (board[i][c1].name != '-')
                                        return false;
                }
        }

        //Knight
        if (x == 'N') {
                if (!((abs(r2 - r1) == 2 and abs(c2 - c1) == 1) or (abs(c2 - c1) == 2 and abs(r2 - r1) == 1)))
                        return false;
        }

        //Bishop
        if (x == 'B') {
                if (abs(r2 - r1) != abs(c2 - c1))
                        return false;
                int s1 = (r2 > r1? 1: -1),
                    s2 = (c2 > c1? 1: -1);
                for (int i = 1; i < abs(r2 - r1); i++)
                        if (board[r1 + s1 * i][c1 + s2 * i].name != '-')
                                return false;
        }

        //Queen
        if (x == 'Q') {
                bool flag1 = true, flag2 = true;

                //A queen can move like a rook or a bishop so for each of them we make a flag to check-
                //if it's right or wrong to move

                //rook
                if (r1 != r2 and c1 != c2)
                        flag1 = false;
                if (c1 == c2) {
                        for (int i = min(r1, r2) + 1; i < max(r1, r2); i++)
                                if (board[i][c1].name != '-')
                                        flag1 = false;
                }
                else {
                        for (int i = min(c1, c2) + 1; i < max(c1, c2); i++)
                                if (board[r1][i].name != '-')
                                        flag1 = false;
                }

                //bishop
                if (abs(r2 - r1) != abs(c2 - c1))
                        flag2 = false;
                int s1 = (r2 > r1? 1: -1),
                    s2 = (c2 > c1? 1: -1);
                for (int i = 1; i < abs(r2 - r1); i++)
                        if (board[r1 + s1 * i][c1 + s2 * i].name != '-')
                                flag2 = false;

                if (!flag1 and !flag2)
                        return false;
        }

        //King
        if (x == 'K') {
                if (abs(r2 - r1) > 1 or abs(c2 - c1) > 1)
                        return false;
        }


        //Check if after moving the king is in danger or not
        Piece tmp = board[r2][c2];
        board[r1][c1].change('-', '-');
        board[r2][c2].change(x, y);

        if (ischeck(y)) {
                board[r1][c1].change(x, y);
                board[r2][c2] = tmp;
                return false;
        }

        board[r1][c1].change(x, y);
        board[r2][c2] = tmp;
        return true;
}
void Chess::move(string s) {
        //Surrender
        if (s == "fin") {
                if (turn == 'W')
                        stat.setString("Black Wins");
                else
                        stat.setString("White Wins");
                isfin = true;
        }


        //Decrypting the string
        int c1 = int(s[0] - 'a') + 1,
            r1 = 9 - int(s[1] - '0'),
            c2 = int(s[4] - 'a') + 1,
            r2 = 9 - int(s[5] - '0');
        char na = s[2];
        char col = s[3];

        //Check if it is wrong or right to move
        if (col != turn) {
                stat.setString("not your turn");
                return;
        }
        if (rmove(r1, c1, r2, c2, na, col)) {
                board[r1][c1].change('-', '-');
                board[r2][c2].change(na, col);
        }
        else {
                stat.setString("try again");
                return;
        }

        //Changing turns
        if (turn == 'W')	turn = 'B';
        else	turn = 'W';

        //Check if it's a check mate or not
        if (ismate(turn)) {
                if (turn == 'W')
                        stat.setString("Black Wins");
                else
                        stat.setString("White Wins");
                isfin = true;
        }

}

void Chess::draw() {
        for (int i = 1; i < 9; i++)
                for (int j = 1; j < 9; j++) {
                        window -> draw(board[i][j].rect);
                        if (board[i][j].name != '-')
                                window -> draw(board[i][j].sp);
                }
        window -> draw(stat);
}

void Chess::mouse_clicked(const sf::Vector2i& pos) {
        int r = get_ind(pos.y), c = get_ind(pos.x);
        if (r == -1 or c == -1)
                return;
        if (oneClick) { /////////////////////////////////
                oneClick = false;
        }
        else { /////////////////////////////////////////
                oneClick = true;
        }
}

void Chess::stat_upd() {
        if (this -> isfin) {
                if (turn == 'W')
                        this -> stat.setString("Black Wins");
                else
                        this -> stat.setString("White Wins");
        }
        else {
                if (turn == 'W')
                        this -> stat.setString("White turn");
                else
                        this -> stat.setString("Black turn");
        }
}

void Chess::run() {
        this -> init();
        this -> window -> display();
        while (this -> window -> isOpen()) {
                sf::Event event;
                while (this -> window -> pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                this -> window -> close();
                        }
                        if (!this -> isfin && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                this -> mouse_clicked(sf::Mouse::getPosition(*(this -> window)));
                        }
                }
                this -> window -> clear(sf::Color(150, 150, 150));
                this -> stat_upd();
                this -> draw();
                this -> window -> display();
        }
}
