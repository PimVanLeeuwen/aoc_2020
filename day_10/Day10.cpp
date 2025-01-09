#include "Day10.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <map>
#include <ostream>
#include <set>

using namespace std;

void Day10::execute(const vector<string> &lines) {
    vector adapters = {0};

    for (const auto &line: lines) adapters.push_back(stoi(line));
    sort(adapters.begin(), adapters.end());
    adapters.push_back(adapters.back()+3);

    pair diffs = {0, 0};
    for (int i = 0; i < adapters.size(); i++) {
        if (i > 0 && adapters[i] - adapters[i-1] == 1) diffs.first++;
        if (i > 0 && adapters[i] - adapters[i-1] == 3) diffs.second++;
    }

    cout << "Part 1: " << diffs.first*diffs.second << endl;

    map<long, long> ways_to_reach = {{0,1}};

    for (const int jolt : adapters) {
        if (jolt == 0) continue;
        for (int i = jolt - 1; i >= jolt - 3; i--) ways_to_reach[jolt] += ways_to_reach[i];
    }

    cout << "Part 2: " << ways_to_reach[adapters.back()] << endl;
}
