#include "Day3.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <sstream>
#include <iostream>
#include <numeric>
using namespace std;

void Day3::execute(const vector<string>& lines) {
    vector<vector<char>> matrix;

    for (const auto &line: lines) {
        vector<char> matrix_line;
        for (char c : line) matrix_line.push_back(c);
        matrix.push_back(matrix_line);
    }

    vector<int> trees_per_slope;
    vector<pair<int, int>> slopes = {{1,1}, {3,1}, {5,1}, {7,1}, {1, 2}};

    for (const auto [x_slope,y_slope] : slopes) {
        int x = 0, y = 0, trees = 0;
        while (y < matrix.size() - y_slope) {
            x += x_slope; y += y_slope;
            if (matrix[y][x % matrix[0].size()] == '#') trees++;
        }
        trees_per_slope.push_back(trees);
    }

    cout << "Part 1: " << trees_per_slope[1] << endl;
    cout << "Part 2: " << accumulate(trees_per_slope.begin(), trees_per_slope.end(), 1, multiplies<>{}) << endl;
}