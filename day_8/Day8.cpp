#include "Day8.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <sstream>

using namespace std;

pair<bool, long> terminates(const vector<tuple<string, char, int>>& matrix) {
    set<long> executed_pointers;
    long pointer = 0, accumulator = 0;

    while (executed_pointers.find(pointer) == executed_pointers.end()) {
        if (pointer == matrix.size()) return make_pair(true, accumulator);
        executed_pointers.insert(pointer);
        if (get<0>(matrix[pointer]) == "nop") {
            pointer++;
        } else if (get<0>(matrix[pointer]) == "acc") {
            get<1>(matrix[pointer]) == '+' ? accumulator += get<2>(matrix[pointer]) : accumulator -= get<2>(matrix[pointer]);
            pointer++;
        } else {
            get<1>(matrix[pointer]) == '+' ? pointer += get<2>(matrix[pointer]) : pointer -= get<2>(matrix[pointer]);
        }
    }

    return make_pair(false, accumulator);
}

void Day8::execute(const vector<string> &lines) {
    vector<tuple<string, char, int>> matrix;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line); string token;
        vector<string> matrix_line;

        // separate line
        while (getline(ss, token, ' ')) matrix_line.push_back(token);

        matrix.emplace_back(matrix_line[0], matrix_line[1][0],
            stoi(matrix_line[1].substr(1, matrix_line[1].length() - 1)));
    }

    cout << "Part 1: " << terminates(matrix).second << endl;

    for (int i = 0; i < matrix.size(); i++) {
        if (get<0>(matrix[i]) == "acc") continue;

        get<0>(matrix[i]) == "nop" ? get<0>(matrix[i]) = "jmp" : get<0>(matrix[i]) = "nop";
        if (terminates(matrix).first) cout << "Part 2: " << terminates(matrix).second << endl;
        get<0>(matrix[i]) == "nop" ? get<0>(matrix[i]) = "jmp" : get<0>(matrix[i]) = "nop";
    }
}
