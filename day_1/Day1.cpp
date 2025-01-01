#include "Day1.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

void Day1::execute(const vector<string>& lines) {
    long part_1 = 0, part_2 = 0;
    set<int> numbers;

    for (const auto &line: lines) numbers.insert(stoi(line));

    for (const auto &n1 : numbers) {
          for (const auto &n2 : numbers) {
              if (n1 + n2 == 2020) {part_1 = n1*n2; break;}
          }
    }

    cout << "Part 1: " << part_1 << endl;

    for (const auto &n1 : numbers) {
        for (const auto &n2 : numbers) {
            for (const auto &n3 : numbers) {
                if (n1 + n2 + n3 == 2020) {part_2 = n1*n2*n3; break;}
            }
        }
    }

    cout << "Part 2: " << part_2 << endl;
}

