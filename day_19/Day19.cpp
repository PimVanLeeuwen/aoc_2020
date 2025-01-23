#include "Day19.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <regex>

using namespace std;

string build_regex(const map<int, string>& rules, const int i=0) {
    if (rules.at(i).find('"') != string::npos) {
        return rules.at(i).substr(1, 1);
    }

    stringstream ss(rules.at(i)); string token;
    string output;

    while (getline(ss, token, ' ')) {
        if (token == "|") output += '|';
        else if (token == "+") output += '+';
        else output += build_regex(rules, stoi(token));
    }

    return "(" + output + ")";
}

void Day19::execute(const vector<string> &lines) {
    long part_1 = 0, part_2 = 0;
    map<int, string> rules;

    vector<string> messages;

    for (const auto &line: lines) {
        if (line.find(':') != string::npos) {
            rules[stoi(line.substr(0, line.find(":")))] = line.substr(line.find(":") + 2);
        }
        else if (!line.empty()) messages.push_back(line);
    }

    regex rule_0(build_regex(rules) + "$");

    map<int, string> rules_2 = rules;

    // smart convert 42 | 42 8 into 42+
    rules_2.at(8) = "42 +";
    // for 11: 42 31 | 42 11 31 we manually unrolled until depth was deep enough.
    rules_2.at(11) = "42 31 | 42 42 31 31 | 42 42 42 31 31 31 | 42 42 42 42 31 31 31 31 | 42 42 42 42 42 31 31 31 31 31";

    regex rule_2(build_regex(rules_2) + "$");

    for (auto m : messages) {
        if (regex_match(m, rule_0)) part_1++;
        if (regex_match(m, rule_2)) part_2++;
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
