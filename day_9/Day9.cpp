#include "Day9.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <sstream>
#include <ostream>
#include <set>
#include <utility>

using namespace std;

void Day9::execute(const vector<string> &lines) {
    long part_1 = 0;
    deque<long> numbers;
    vector<long> numbers_list;

    for (const auto &line: lines) {
        if (numbers.size() < 25) numbers.push_back(stol(line));
        else {
            bool found = false;
            for (int i = 0; i < 25; i++) {
                for (int j = i + 1; j < 25; j++) if (numbers[i] + numbers[j] == stol(line)) { found = true; break; }
                if (found) break;
            }

            if (!found) {
                part_1 = stoi(line); cout << "Part 1: " << part_1 << endl;
                break;
            }

            numbers.push_back(stol(line)); numbers.pop_front();
        }
    }

    for (const auto &line: lines) numbers_list.push_back(stol(line));

    int left = 0;
    int right = 1;

    vector sum_list(numbers_list.begin() + left, numbers_list.begin() + right);
    long sum = accumulate(sum_list.begin(), sum_list.end(), 0);

    while (sum != part_1) {
        if (sum > part_1) left++;
        else right++;

        sum_list = vector<long>(numbers_list.begin() + left, numbers_list.begin() + right);
        sum = accumulate(sum_list.begin(), sum_list.end(), 0);
    }


    cout << "Part 2: " << *min_element(sum_list.begin(), sum_list.end()) + *max_element(sum_list.begin(), sum_list.end()) << endl;
}


