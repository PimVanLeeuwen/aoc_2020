#include "Day13.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

// (num + -10) % 41 == 0
// (num + 0) % 521 == 0
// (num + 8) % 23 == 0
// (num + 31) % 523 == 0
// (num + 44) % 13 == 0
bool satisfies(const long n) {
    if ((n - 10) % 41 != 0) return false;
    if (n % 521 != 0) return false;
    if ((n + 8) % 23 != 0) return false;
    if ((n + 31) % 523 != 0) return false;
    if ((n + 44) % 13 != 0) return false;

    return true;
}

void Day13::execute(const vector<string> &lines) {
    const int time = stoi(lines.front());

    stringstream ss(lines.back()); string token;
    int bus = -1; int time_wait = -1; int index = 0;
    vector<pair<int, int>> busses;

    // separate line
    while (getline(ss, token, ',')) {
        if (token != "x" && bus == -1) { bus = stoi(token); time_wait = bus - (time % bus); }
        else if (token != "x" && stoi(token) - (time % stoi(token)) < time_wait) { bus = stoi(token); time_wait = bus - (time % bus); }

        if (token != "x") busses.emplace_back(stoi(token),index);
        index++;
    }

    for (const auto [bus, index] : busses) {
        cout << "(num + " << index - 19 << ") % " << bus << " == 0" << endl;
    }

    // (num + -19) % 19 == 0
    // (num + 17) % 17 == 0
    // (num + 29) % 29 == 0
    // (num + 37) % 37 == 0
    long multiple = 19 * 17 * 29 * 37;

    while (!satisfies(multiple)) multiple += 19 * 17 * 29 * 37;

    cout << "Part 1: " << bus*time_wait << endl;
    cout << "Part 2: " << multiple - 19 << endl;
}
