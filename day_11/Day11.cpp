#include "Day11.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

vector<pair<int, int>> neighbours = {
    {-1, -1}, {1,1}, {-1, 1}, {1, -1},
    {0,1}, {0,-1}, {1,0}, {-1, 0}
};

vector<vector<char>> simulate_step(const vector<vector<char>> &input) {
    vector<vector<char>> output = input;

    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
            if (input[y][x] == '.') continue;
            int count_occupied = 0;
            for (const auto [diff_y, diff_x] : neighbours) {
                if (input[y + diff_y][x + diff_x] == '#') count_occupied ++;
            }

            if (input[y][x] == 'L' && count_occupied == 0) output[y][x] = '#';
            if (input[y][x] == '#' && count_occupied >= 4) output[y][x] = 'L';
        }
    }

    return output;
}

vector<vector<char>> simulate_step_part_2(const vector<vector<char>> &input) {
    vector<vector<char>> output = input;

    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
            if (input[y][x] == '.') continue;
            int count_occupied = 0;
            for (const auto [diff_y, diff_x] : neighbours) {
                int i = 1;
                while (y + diff_y * i < input.size() && y + diff_y * i >= 0 && x + diff_x * i < input[y].size() && x + diff_x * i >= 0) {
                    if (input[y + diff_y * i][x + diff_x * i] == '#') {count_occupied ++; break; }
                    if (input[y + diff_y * i][x + diff_x * i] == 'L') break;
                    i++;
                }
            }

            if (input[y][x] == 'L' && count_occupied == 0) output[y][x] = '#';
            if (input[y][x] == '#' && count_occupied >= 5) output[y][x] = 'L';
        }
    }

    return output;
}

void Day11::execute(const vector<string> &lines) {

    vector<vector<char>> matrix = {vector(static_cast<int>(lines[0].size()) + 2, '.')};


    for (const auto &line: lines) {
        vector matrix_line = {'.'};
        for (const auto &l : line) matrix_line.push_back(l);
        matrix_line.push_back('.'); matrix.push_back(matrix_line);
    }

    matrix.emplace_back(static_cast<int>(lines[0].size()) + 2, '.');

    vector<vector<char>> matrix_part_2 = matrix;

    vector<vector<char>> new_matrix = simulate_step(matrix);

    while (new_matrix != matrix) {
        matrix = new_matrix;
        new_matrix = simulate_step(matrix);
    }

    long part_1 = 0;
    for (const auto& line : matrix) for (const auto l : line) if (l == '#') part_1++;
    cout << "Part 1: " << part_1 << endl;

    vector<vector<char>> new_matrix_part_2 = simulate_step_part_2(matrix_part_2);

    while (new_matrix_part_2 != matrix_part_2) {
        matrix_part_2 = new_matrix_part_2;
        new_matrix_part_2 = simulate_step_part_2(matrix_part_2);
    }

    long part_2 = 0;
    for (const auto& line : matrix_part_2) for (const auto l : line) if (l == '#') part_2++;
    cout << "Part 2: " << part_2 << endl;
}
