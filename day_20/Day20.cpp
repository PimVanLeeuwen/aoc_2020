#include "Day20.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <ostream>
#include <sstream>

using namespace std;

struct tile {
    int id{};
    vector<string> square;

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


void Day20::execute(const vector<string> &lines) {
    long part_1 = 1, part_2 = 0;
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

    cout << images.size() << endl;

    if (floor(sqrt(images.size()) != ceil(sqrt(images.size())))) throw invalid_argument("number not a square");

    int image_size = static_cast<int>(sqrt(images.size()));

    for (const tile *t : images) {
        int neighbours = 0;
        for (const tile *t2 : images) {
            if (t->neighbour_of(*t2)) neighbours++;
        }
        if (neighbours == 2) part_1 *= t->id;
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
