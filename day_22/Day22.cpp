#include "Day22.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <sstream>

using namespace std;

map<pair<deque<int>, deque<int>>, pair<int, deque<int>>> memoization;


pair<int, deque<int>> part_2_game(deque<int> player_1, deque<int> player_2) {
    if (memoization.find({player_1, player_2}) != memoization.end()) return memoization.at({player_1, player_2});
    deque<int> player_1_copy = player_1;
    deque<int> player_2_copy = player_2;

    set<pair<deque<int>, deque<int>>> played_already;
    while (!(player_1.empty() || player_2.empty())) {
        if (played_already.find({player_1, player_2}) != played_already.end()) return {1, player_1};
        played_already.emplace(player_1, player_2);

        const int p1 = player_1.front(); player_1.pop_front();
        const int p2 = player_2.front(); player_2.pop_front();

        if (p1 <= player_1.size() && p2 <= player_2.size()) {
            deque<int> p1_temp; for (int i = 0 ; i < p1; i++) p1_temp.push_back(player_1[i]);
            deque<int> p2_temp; for (int i = 0 ; i < p2; i++) p2_temp.push_back(player_2[i]);
            if (auto [winner, winning_stack] = part_2_game(p1_temp, p2_temp); winner == 1) {
                player_1.push_back(p1); player_1.push_back(p2);
            } else {
                player_2.push_back(p2); player_2.push_back(p1);
            }
        } else if (p2 > p1) {
            player_2.push_back(p2); player_2.push_back(p1);
        } else {
            player_1.push_back(p1); player_1.push_back(p2);
        }
    }

    if (player_1.empty()) {
        memoization[{player_1_copy, player_2_copy}] = {2, player_2};
        return {2, player_2};
    } else {
        memoization[{player_1_copy, player_2_copy}] = {1, player_1};
        return {1, player_1};
    }

}

void Day22::execute(const vector<string> &lines) {
    long part_1 = 0, part_2 = 0;
    deque<int> player_1;
    deque<int> player_2;
    bool player_1_processing = true;

    for (const auto &line: lines) {
        if (line.empty()) {
            player_1_processing = false;
        } else if (player_1_processing && isdigit(line[0])) {
            player_1.push_back(stoi(line));
        } else if (isdigit(line[0])) {
            player_2.push_back(stoi(line));
        }
    }

    const deque<int> player_1_2 = player_1;
    const deque<int> player_2_2 = player_2;

    while (!(player_1.empty() || player_2.empty())) {
        const int p1 = player_1.front(); player_1.pop_front();
        const int p2 = player_2.front(); player_2.pop_front();

        if (p2 > p1) {
            player_2.push_back(p2); player_2.push_back(p1);
        } else {
            player_1.push_back(p1); player_1.push_back(p2);
        }
    }

    deque<int> winning = player_1.empty() ? player_2 : player_1;

    int i = 1;
    while (!winning.empty()) { part_1 += winning.back()*i; winning.pop_back(); i++; }

    auto [winner, winning_stack] = part_2_game(player_1_2, player_2_2);
    i = 1;
    while (!winning_stack.empty()) { part_2 += winning_stack.back()*i; winning_stack.pop_back(); i++; }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
