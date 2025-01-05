#include "Day6.h"

#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

void Day6::execute(const vector<string> &lines) {

    long part_1 = 0, part_2 = 0;
    set<char> yes;
    map<char, int> yes_map;
    int group_size = 0;

    for (const auto &line: lines) {
        if (line.empty()) {
            part_1 += static_cast<long>(yes.size());
            for (const auto [c, l] : yes_map) if (l == group_size) part_2++;
            yes.clear(); yes_map.clear(); group_size = 0; continue;
        }

        for (const auto &c: line) { yes.insert(c); yes_map[c]++; }

        group_size++;
    }

    part_1 += static_cast<long>(yes.size());
    for (const auto [c, l] : yes_map) if (l == group_size) part_2++;

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
