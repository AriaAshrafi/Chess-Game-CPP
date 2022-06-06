#include <bits/stdc++.h>
#include <Others.h>
using namespace std;

sf::Vector2f get_pos(int r, int c) {
        return sf::Vector2f(setting::cell_offset + c * ( setting::cell_size + setting::line_space),
                        setting::cell_offset + r * ( setting::cell_size + setting::line_space));
}

int get_ind(int x) {
        x -= setting::cell_offset;
        if (x < 0)
                return -1;
        int cell_plus_space = setting::cell_size + setting::line_space;
        int index = x / cell_plus_space;
        if (index < 1 || index > 9 || x > index * cell_plus_space + setting::cell_size)
                return -1;
        return index;
}
