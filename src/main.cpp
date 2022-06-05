#include <bits/stdc++.h>
#include <Chess.h>
#include <Piece.h>
#include <Setting.h>
#include <Others.h>
using namespace sf;

int main() {
        
        RenderWindow window(VideoMode(1080, 1080), "Tic Tac Toe", Style::Titlebar | Style::Close);
        Chess game(&window);
        game.run();	
	return 0;
}
