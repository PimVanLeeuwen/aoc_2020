#include "Day5.h"

#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void Day5::execute(const vector<string> &lines) {
    int part_1 = 0;
    set<int> taken;

    for (const auto &line: lines) {
        string row = line.substr(0, 7);
        string seat = line.substr(7, 3);

        int row_low = 0, row_high = 127;
        int seat_low = 0, seat_high = 7;

        for (const char &r : row) {
            const int half = (row_high - row_low + 1)/2;
            (r == 'B') ? row_low += half : row_high -= half;
        }

        for (const char &s : seat) {
            const int half = (seat_high - seat_low + 1)/2;
            (s == 'R') ? seat_low += half : seat_high -= half;
        }

        part_1 = max(part_1, row_low*8 + seat_low);

        taken.insert(row_low*8 + seat_low);
    }

    cout << "Part 1: " << part_1 << endl;

    int prev = -1;
    for (const int i : taken) {
        if (i == prev + 2) cout << "Part 2: " << i-1 << endl;
        prev = i;
    }
}
