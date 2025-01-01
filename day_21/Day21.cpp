#include "Day21.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

void Day21::execute(const vector<string> &lines) {
    long part_1 = 0, part_2 = 0;
    vector<vector<string>> matrix;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line); string token;
        vector<string> matrix_line;

        // separate line
        while (getline(ss, token, ' ')) matrix_line.push_back(token);

        matrix.push_back(matrix_line);
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
