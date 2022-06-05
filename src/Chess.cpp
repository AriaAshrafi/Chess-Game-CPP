#include <bits/stdc++.h>
#include <Chess.h>
using namespace std;


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
            cout << "black win" << endl;
        else
            cout << "white win" << endl;
        exit(0);
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
        cout << "not your turn" << endl;
        return;
    }
    if (rmove(r1, c1, r2, c2, na, col)) {
        board[r1][c1].change('-', '-');
        board[r2][c2].change(na, col);
        cout << "done" << endl;
    }
    else {
        cout << "try again" << endl;
        return;
    }

    //Changing turns
    if (turn == 'W')	turn = 'B';
    else	turn = 'W';

    //Check if it's a check mate or not
    if (ismate(turn)) {
        if (turn == 'W')
            cout << "black win" << endl;
        else
            cout << "white win" << endl;
        exit(0);
    }

}
