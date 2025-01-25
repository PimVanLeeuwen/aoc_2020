#include "Day20.h"

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <ostream>
#include <sstream>

using namespace std;

struct tile {
    int id{};
    bool rotate{false};
    vector<string> square;
    pair<int, int> pos{-1, -1};

    [[nodiscard]] vector<string> get_edges() const {
        vector output = {square.back(), square.front()};

        string left, right;
        for (string line : square) { left += line[0]; right += line[line.size()-1]; }
        output.push_back(left); output.push_back(right);

        output.push_back(reverse_string(square.back()));
        output.push_back(reverse_string(square.front()));
        output.push_back(reverse_string(left));
        output.push_back(reverse_string(right));

        return output;
    }

    [[nodiscard]] vector<string> cropped_square() const {
        vector<string> output;
        for (int i = 1; i < square.size() - 1; i++) {
            output.push_back(square[i].substr(1, square[1].size()-2));
        }
        return output;
    }

    void place(int x, int y) {
        pos = {x, y};
    }

    [[nodiscard]] int x() const {
        return get<0>(pos);
    }

    [[nodiscard]] int y() const {
        return get<1>(pos);
    }

    [[nodiscard]] bool is_placed() const {
        return get<0>(pos) != -1;
    }

    [[nodiscard]] string top() const {
        return square.front();
    }

    [[nodiscard]] string bot() const {
        return square.back();
    }

    [[nodiscard]] string left() const {
        return get_edges()[2];
    }

    [[nodiscard]] string right() const {
        return get_edges()[3];
    }

    [[nodiscard]] int see_monsters() const {
        int count = 0;
        for (int y = 0; y < square.size() - 2; y++) {
            for (int x = 0; x < square.size() - 19; x++) {
                if (square[y+1][x] == '#' && square[y+2][x+1] == '#' && square[y+2][x+4] == '#' &&
                    square[y+1][x+5] == '#' && square[y+1][x+6] == '#' && square[y+2][x+7] == '#' && square[y+2][x+10] == '#' &&
                    square[y+1][x+11] == '#' && square[y+1][x+12] == '#' && square[y+2][x+13] == '#' && square[y+2][x+16] == '#' &&
                    square[y+1][x+17] == '#' && square[y+1][x+18] == '#' && square[y+1][x+19] == '#' && square[y][x+18] == '#') {
                    count++;
                }
            }
        }

        return count;
    }

    [[nodiscard]] int hash_tags() const {
        int count = 0;
        for (const string& line : square) {
            for (const char c : line) {
                if (c == '#') count++;
            }
        }
        return count;
    }

    void rotate_90() {
        vector rotated(square.size(), string(square.size(), ' '));
        for (int i = 0; i < square.size(); i++) {
            for (int j = 0; j < square.size(); j++) {
                rotated[j][square.size() - 1 - i] = square[i][j];
            }
        }
        square = rotated;
    }

    void flip() {
        vector flipped(square.size(), string(square.size(), ' '));
        for (int i = 0; i < square.size(); i++) {
            for (int j = 0; j < square.size(); j++) {
                flipped[i][square.size() - 1 - j] = square[i][j];
            }
        }
        square = flipped;
    }

    void next_orientation() {
        if (rotate) {
            flip();
            rotate_90();
            rotate = false;
        } else {
            flip();
            rotate = true;
        }
    }

    [[nodiscard]] vector<string> shared_edge(const tile& other) const {
        vector<string> output;
        vector<string> other_edges = other.get_edges();
        for (const auto& e : get_edges()) {
            if (find(other_edges.begin(), other_edges.end(), e) != other_edges.end()) {
                output.push_back(e);
            }
        }
        return output;
    }

    [[nodiscard]] bool neighbour_of(const tile& other) const {
        return other.id != id && !shared_edge(other).empty();
    }

    private:
        [[nodiscard]] static string reverse_string(const string& str) {
            return {str.rbegin(), str.rend()};
        }
};

bool everything_placed(vector<tile*> tiles) {
    return all_of(tiles.begin(), tiles.end(), [](const tile* t){return t->is_placed();});
}

void Day20::execute(const vector<string> &lines) {
    long part_1 = 1;
    vector<tile*> images;

    int number = -1;
    vector<string> image;

    for (const auto &line: lines) {

        if (line.find("Tile") != string::npos) {
            number = stoi(line.substr(line.find(" " + 1, 4)));
        } else if (line.empty()) {
            images.emplace_back(new tile());
            images.back()->id = number;
            images.back()->square = image;
            number = -1;
            image.clear();
        } else {
            image.push_back(line);
        }
    }

    if (number != -1) {
        images.emplace_back(new tile());
        images.back()->id = number;
        images.back()->square = image;
    }

    if (floor(sqrt(images.size()) != ceil(sqrt(images.size())))) throw invalid_argument("number not a square");

    int image_size = static_cast<int>(sqrt(images.size()));

    tile* top_left = nullptr;

    for (tile* t : images) {
        int neighbours = 0;
        for (const tile* t2 : images) {
            if (t->neighbour_of(*t2)) neighbours++;
        }
        if (neighbours == 2) part_1 *= t->id;
        if (neighbours == 2) top_left = t;
    }

    vector<tile*> neighbours_top_left;


    for (tile* t2 : images) {
        if (top_left->neighbour_of(*t2)) neighbours_top_left.push_back(t2);
    }

    tuple rotations_done = {0,0,0};

    while (!((neighbours_top_left.back()->top() ==  top_left->bot() && neighbours_top_left.front()->left() ==  top_left->right()) ||
        (neighbours_top_left.front()->top() ==  top_left->bot() && neighbours_top_left.back()->left() ==  top_left->right()))) {
        if (get<2>(rotations_done) < 7) {
            cout << 2 << endl;
            get<2>(rotations_done)++;
            neighbours_top_left.back()->next_orientation();
        } else if (get<1>(rotations_done) < 7) {
            cout << 1 << endl;
            get<1>(rotations_done)++;
            get<2>(rotations_done) = 0;
            neighbours_top_left.front()->next_orientation();
        } else {
            cout << 0 << endl;
            get<0>(rotations_done)++;
            get<1>(rotations_done) = 0;
            get<2>(rotations_done) = 0;
            top_left->next_orientation();
        }
    }

    // place the first three images
    top_left->place(0,0);
    if (neighbours_top_left.back()->top() ==  top_left->bot() && neighbours_top_left.front()->left() ==  top_left->right()) {
        neighbours_top_left.back()->place(0, 1);
        neighbours_top_left.front()->place(1, 0);
    } else {
        neighbours_top_left.front()->place(0, 1);
        neighbours_top_left.back()->place(1, 0);
    }

    deque<tile*> to_place;
    for (tile* t : images) {
        if (t->id != top_left->id && t->id != neighbours_top_left.back()->id && t->id != neighbours_top_left.front()->id) to_place.push_back(t);
    }

    while (!to_place.empty()) {
        tile* potential_tile = to_place.front(); to_place.pop_front();
        bool placed = false;

        for (const tile* t : images) {
            if (t->is_placed() && t->neighbour_of(*potential_tile)) {
                while (!(potential_tile->top() == t->bot() || potential_tile->bot() == t->top() ||
                    potential_tile->left() == t->right() || potential_tile->right() == t->left())) {
                    potential_tile->next_orientation();
                }
                if (potential_tile->top() == t->bot()) {
                    potential_tile->place(t->x(), t->y() + 1);
                } else if (potential_tile->bot() == t->top()) {
                    potential_tile->place(t->x(), t->y() - 1);
                } else if (potential_tile->left() == t->right()) {
                    potential_tile->place(t->x() + 1, t->y());
                } else if (potential_tile->right() == t->left()) {
                    potential_tile->place(t->x() - 1, t->y());
                } else {
                    throw runtime_error("It must be because it is a neighbour");
                }
                placed = true; break;
            }
        }
        // cannot place this yet, place later
        if (!placed) to_place.push_back(potential_tile);
    }

    vector big_image(image_size * (images.front()->square.size() - 2),
                             string(image_size * (images.front()->square.size() - 2), ' '));

    for (const tile* t : images) {
        vector<string> c = t->cropped_square();
        for (int x = 0; x < c.size(); x++) {
            for (int y = 0; y < c.size(); y++) {
                big_image[t->y()*c.size() + y][t->x()*c.size() + x] = c[y][x];
            }
        }
    }

    const auto big_image_tile = new tile();
    big_image_tile->square = big_image;

    while (big_image_tile->see_monsters() == 0) {
        big_image_tile->next_orientation();
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << big_image_tile->hash_tags() - big_image_tile->see_monsters()*15 << endl;
}
