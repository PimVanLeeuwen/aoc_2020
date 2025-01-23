#include "Day20.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

struct tile {
    int id;
    vector<vector<char>> square_chars;
};


void Day20::execute(const vector<string> &lines) {
    long part_1 = 0, part_2 = 0;
    vector<tile*> images;

    int number = -1;
    vector<vector<char>> image;

    for (const auto &line: lines) {

        if (line.find("Tile") != string::npos) {
            number = stoi(line.substr(line.find(" " + 1, 4)));
        } else if (line.empty()) {
            images.emplace_back(new tile());
            images.back()->id = number;
            images.back()->square_chars = image;
            number = -1;
            image.clear();
        } else {
            vector<char> image_line;
            for (char c : line) image_line.push_back(c);
            image.push_back(image_line);
        }
    }

    if (number != -1) {
        images.emplace_back(new tile());
        images.back()->id = number;
        images.back()->square_chars = image;
    }

    cout << images.size() << endl;

    if (floor(sqrt(images.size()) != ceil(sqrt(images.size())))) throw invalid_argument("number not a square");

    int image_size = static_cast<int>(sqrt(images.size()));



    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
