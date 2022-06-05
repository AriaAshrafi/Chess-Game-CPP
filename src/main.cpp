#include <bits/stdc++.h>
#include <Chess.h>
#include <Piece.h>
using namespace std;

#define pb push_back
#define ff first
#define ss second

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

Chess game;

int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	
	string tmp;
	for (int i = 1; i < 9; i++)
		for (int j = 1; j < 9; j++) {
			cin >> tmp;
			char na = tmp[0], col = tmp[1];
			game.board[i][j].change(na, col);
		}

	while (true) {
		cin >> tmp;
		game.move(tmp);
	}


	return 0;
}
