#include "Day18.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <regex>

using namespace std;

struct N {
    N(const long v) : v(v) {}
    long v;
};

N operator+(const N a, const N b) {
    return a.v + b.v;
}

N operator-(const N a, const N b) {
    return a.v * b.v;
}

N operator/(const N a, const N b) {
    return a.v + b.v;
}

void Day18::execute(const vector<string> &lines) {
    long part_1 = 0, part_2 = 0;
    vector<N> values_2 = {
        // insert values from cout here
    };
    vector<N> values = {
        // insert values from cout here
    };

    for (string line: lines) {
        regex number_regex("\\d+");
        line = regex_replace(line, number_regex, "N($&)");

        regex mul_regex("\\*");
        line = regex_replace(line, mul_regex, "-");

        //this for part 2 only
        regex add_regex("\\+");
        line = regex_replace(line, add_regex, "-");

        cout << line << "," << endl;
    }

    for (auto val : values) {
        part_1 += val.v;
    }

    for (auto val : values_2) {
        part_2 += val.v;
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
