#include "Day17.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

vector<vector<int>> d3_neighbours = {
    {-1, -1, -1}, {-1, -1, 0}, {-1, -1, 1},
    {-1, 1, -1}, {-1, 1, 0}, {-1, 1, 1},
    {-1, 0, -1}, {-1, 0, 0}, {-1, 0, 1},
    {1, -1, -1}, {1, -1, 0}, {1, -1, 1},
    {1, 1, -1}, {1, 1, 0}, {1, 1, 1},
    {1, 0, -1}, {1, 0, 0}, {1, 0, 1},
    {0, -1, -1}, {0, -1, 0}, {0, -1, 1},
    {0, 1, -1}, {0, 1, 0}, {0, 1, 1},
    {0, 0, -1}, {0, 0, 1}
};

vector<vector<int>> d4_neighbours = {
    {-1, -1, -1, -1}, {-1, -1, -1, 0}, {-1, -1, -1, 1},
    {-1, -1, 1, -1}, {-1, -1, 1, 0}, {-1, -1, 1, 1},
    {-1, -1, 0, -1}, {-1, -1, 0, 0}, {-1, -1, 0, 1},
    {-1, 1, -1, -1}, {-1, 1, -1, 0}, {-1, 1, -1, 1},
    {-1, 1, 1, -1}, {-1, 1, 1, 0}, {-1, 1, 1, 1},
    {-1, 1, 0, -1}, {-1, 1, 0, 0}, {-1, 1, 0, 1},
    {-1, 0, -1, -1}, {-1, 0, -1, 0}, {-1, 0, -1, 1},
    {-1, 0, 1, -1}, {-1, 0, 1, 0}, {-1, 0, 1, 1},
    {-1, 0, 0, -1}, {-1, 0, 0, 1}, {-1,0,0,0},
    {1, -1, -1, -1}, {1, -1, -1, 0}, {1, -1, -1, 1},
    {1, -1, 1, -1}, {1, -1, 1, 0}, {1, -1, 1, 1},
    {1, -1, 0, -1}, {1, -1, 0, 0}, {1, -1, 0, 1},
    {1, 1, -1, -1}, {1, 1, -1, 0}, {1, 1, -1, 1},
    {1, 1, 1, -1}, {1, 1, 1, 0}, {1, 1, 1, 1},
    {1, 1, 0, -1}, {1, 1, 0, 0}, {1, 1, 0, 1},
    {1, 0, -1, -1}, {1, 0, -1, 0}, {1, 0, -1, 1},
    {1, 0, 1, -1}, {1, 0, 1, 0}, {1, 0, 1, 1},
    {1, 0, 0, -1}, {1, 0, 0, 1}, {1,0,0,0},
    {0, -1, -1, -1}, {0, -1, -1, 0}, {0, -1, -1, 1},
    {0, -1, 1, -1}, {0, -1, 1, 0}, {0, -1, 1, 1},
    {0, -1, 0, -1}, {0, -1, 0, 0}, {0, -1, 0, 1},
    {0, 1, -1, -1}, {0, 1, -1, 0}, {0, 1, -1, 1},
    {0, 1, 1, -1}, {0, 1, 1, 0}, {0, 1, 1, 1},
    {0, 1, 0, -1}, {0, 1, 0, 0}, {0, 1, 0, 1},
    {0, 0, -1, -1}, {0, 0, -1, 0}, {0, 0, -1, 1},
    {0, 0, 1, -1}, {0, 0, 1, 0}, {0, 0, 1, 1},
    {0, 0, 0, -1}, {0, 0, 0, 1}
};

void Day17::execute(const vector<string> &lines) {
    long part_1 = 0, part_2 = 0;
    constexpr int size = 70;
    vector matrix(size, vector(size, vector(size, '.')));
    vector matrix_2(size, vector(size, vector(size, vector(size, '.'))));

    int y = size/2;
    for (const auto &line: lines) {
        int x = size/2;
        for (const auto c : line) {matrix[size/2][y][x] = c; matrix_2[size/2][size/2][y][x++] = c;}
        y++;
    }

    for (int i = 0; i < 6; i++) {
        vector new_matrix(size, vector(size, vector(size, '.')));
        vector new_matrix_2(size, vector(size, vector(size, vector(size, '.'))));
        for (int w = 1; w < matrix.size() - 1; w++) {
            for (int z = 1; z < matrix.size() - 1; z++) {
                for (int y = 1; y < matrix[z].size() - 1; y++) {
                    for (int x = 1; x < matrix[z][y].size() - 1; x++) {
                        int nr_neighbours = 0;
                        for (const vector<int>& diff : d3_neighbours) {
                            if (matrix[z + diff[0]][y + diff[1]][x + diff[2]] == '#') nr_neighbours++;
                        }

                        if (matrix[z][y][x] == '#' && !(nr_neighbours == 2 || nr_neighbours == 3)) new_matrix[z][y][x] = '.';
                        else if (matrix[z][y][x] == '.' && nr_neighbours == 3) new_matrix[z][y][x] = '#';
                        else new_matrix[z][y][x] = matrix[z][y][x];

                        int nr_neighbours_2 = 0;
                        for (const vector<int>& diff : d4_neighbours) {
                            if (matrix_2[w + diff[0]][z + diff[1]][y + diff[2]][x + diff[3]] == '#') nr_neighbours_2++;
                        }

                        if (matrix_2[w][z][y][x] == '#' && !(nr_neighbours_2 == 2 || nr_neighbours_2 == 3)) new_matrix_2[w][z][y][x] = '.';
                        else if (matrix_2[w][z][y][x] == '.' && nr_neighbours_2 == 3) new_matrix_2[w][z][y][x] = '#';
                        else new_matrix_2[w][z][y][x] = matrix_2[w][z][y][x];
                    }
                }
            }
        }
        matrix = new_matrix;
        matrix_2 = new_matrix_2;
    }

    for (const vector<vector<char>>& mat : matrix) for (const vector<char>& ma : mat) for (const char m : ma) if (m == '#') part_1++;

    for (const vector<vector<vector<char>>>& matri : matrix_2 )for (const vector<vector<char>>& mat : matri) for (const vector<char>& ma : mat) for (const char m : ma) if (m == '#') part_2++;
    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
