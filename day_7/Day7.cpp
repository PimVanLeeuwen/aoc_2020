#include "Day7.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <limits.h>
#include <map>
#include <sstream>

using namespace std;

bool contains_shiny_gold(map<string, vector<pair<int, string>>> &map, const string& word) {
    if (word == "shiny gold") return true;
    if (map.find(word) == map.end()) return false;

    for (const auto &[count, bag] : map.at(word)) {
        if (contains_shiny_gold(map, bag)) return true;
    }

    return false;
}

void Day7::execute(const vector<string> &lines) {
    long part_1 = 0, part_2 = -1;
    vector<vector<string>> matrix;

    map<string, vector<pair<int, string>>> bags;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line); string token;
        vector<string> matrix_line;

        // separate line
        while (getline(ss, token, ' ')) matrix_line.push_back(token);

        string c_bag = matrix_line[0] + " " + matrix_line[1];
        vector<pair<int, string>> o_bags;

        for (int i = 0; i < matrix_line.size(); i++) {
            if (all_of(matrix_line[i].begin(), matrix_line[i].end(), ::isdigit)) {
                o_bags.emplace_back(stoi(matrix_line[i]), matrix_line[i + 1] + " " + matrix_line[i + 2]);
            }
        }

        bags[c_bag] = o_bags;

    }

    for (const auto &[outer_bag, containing_bags] : bags) {
        for (const auto &[count, inner_bag] : containing_bags) {
            if (contains_shiny_gold(bags, inner_bag)) { part_1++; break; }
        }
    }

    deque<pair<int, string>> count_part_2 = {{1, "shiny gold"}};

    while (!count_part_2.empty()) {
        const auto [number, current_bag] = count_part_2.front(); count_part_2.pop_front();

        part_2 += number;

        for (const auto &[number_2, inner_bag] : bags.at(current_bag)) count_part_2.emplace_back(number*number_2, inner_bag);
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
