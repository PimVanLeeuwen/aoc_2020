#include "Day15.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

void Day15::execute(const vector<string> &lines) {
    vector starting_numbers = {0,1,4,13,15,12,16};
    map<int, pair<int, int>> last_seen = {{0, {-1, -1}}};

    for (int i = 0; i < 30000000; i++) {
        if (i < starting_numbers.size()) {
            last_seen[starting_numbers[i]] = {-1, i};
            continue;
        }

        const int last_num = starting_numbers[i-1];
        const int last_index = last_seen[last_num].first;

        (last_index == -1) ? starting_numbers.push_back(0) : starting_numbers.push_back(i - 1 - last_index);

        if (last_seen.find(starting_numbers[i]) == last_seen.end()) {
            last_seen[starting_numbers[i]] = {-1, i};
        } else {
            last_seen[starting_numbers[i]].first = last_seen[starting_numbers[i]].second;
            last_seen[starting_numbers[i]].second = i;
        }

        if (i == 2019) cout << "Part 1: " << starting_numbers.back() << endl;
    }

    cout << "Part 2: " << starting_numbers.back() << endl;
}
