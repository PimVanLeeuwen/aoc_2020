#include "Day2.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
using namespace std;

void Day2::execute(const vector<string>& lines) {
    long part_1 = 0, part_2 = 0;
    vector<vector<string>> matrix;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line); string token;
        vector<string> matrix_line;
        int lower = -1, upper = -1;
        char limit = '-';

        // separate line
        while (getline(ss, token, ' ')) {
            if (lower == -1) {
                int split = 0; while (isdigit(token[split])) split++;
                lower = stoi(token.substr(0, split));
                upper = stoi(token.substr(split + 1, token.length() - split - 1));
            } else if (limit == '-') {
                limit = token[0];
            } else {
                long occurence = count_if(token.begin(), token.end(), [limit](const char c){return c == limit;});
                if (occurence >= lower && occurence <= upper) part_1++;
                if ((token[lower-1] == limit && token[upper-1] != limit) || (token[lower-1] != limit && token[upper-1] == limit)) part_2++;
            }

        }

        matrix.push_back(matrix_line);
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
