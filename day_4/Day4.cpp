#include "Day4.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

set<string> required = {
    "byr",
    "iyr",
    "eyr",
    "hgt",
    "hcl",
    "ecl",
    "pid",
};

bool valid_passport(const map<string, string>& passport) {
    return all_of(required.begin(), required.end(),
        [passport](const string& s){ return passport.find(s) != passport.end();});
}

void Day4::execute(const vector<string> &lines) {

    long part_1 = 0, part_2 = 0;
    vector<vector<string>> matrix;

    map<string, string> passport;
    bool part_2_check = true;

    for (const auto &line: lines) {
        if (line.empty()) {
            if (valid_passport(passport)) part_1++;
            if (valid_passport(passport) && part_2_check) part_2++;
            passport.clear();
            part_2_check = true;
        } else {

            // convert into a string stream to split on token
            stringstream ss(line); string token;
            vector<string> matrix_line;

            // separate line
            while (getline(ss, token, ' ')) {
                string id = token.substr(0, token.find(':'));
                string val = token.substr(token.find(':') + 1);

                passport[id] = val;
                if (id == "byr") {
                    if (const int year = stoi(val);  val.size() != 4 || year < 1920 || year > 2002) part_2_check = false;
                } else if (id == "iyr") {
                    if (const int year = stoi(val); val.size() != 4 || year < 2010 || year > 2020) part_2_check = false;
                } else if (id == "eyr") {
                    if (const int year = stoi(val); val.size() != 4 || year < 2020 || year > 2030) part_2_check = false;
                } else if (id == "hgt") {
                    if (const string indicator = val.substr(val.size()-2); (indicator != "cm" && indicator != "in") ||
                        (indicator == "cm" && (stoi(val.substr(0, val.size()-2)) < 150 || stoi(val.substr(0, val.size()-2)) > 193)) || (indicator != "cm" && (stoi(val.substr(0, val.size()-2)) < 59 || stoi(val.substr(0, val.size()-2)) > 76))) part_2_check = false;
                } else if (id == "hcl") {
                    int size = val.size();
                    bool check = true;
                    for (const char c : val.substr(1)) {
                        if (!isdigit(c) && c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e' && c != 'f') check = false;
                    }
                    if (val[0] != '#' || !check || size != 7) part_2_check = false;
                } else if (id == "ecl") {
                    if (val != "amb" && val != "blu" && val != "brn" && val != "gry" && val != "grn" && val != "hzl" && val != "oth") part_2_check = false;
                } else if (id == "pid") {
                    if (val.size() != 9 || any_of(val.begin(), val.end(), [](const char c){return !isdigit(c);})) part_2_check = false;
                }
            }
        }
    }

    if (!passport.empty() && valid_passport(passport)) part_1++;
    if (!passport.empty() && part_2_check) part_2++;

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
