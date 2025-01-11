#include "Day14.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

string ltob(long n) {
    string output(36, '0');
    for (int i = 0; i < 36; i++) {
        if (n / static_cast<long>(pow(2, 35 - i)) > 0) {n %= static_cast<long>(pow(2, 35 - i)); output[i] = '1';}
    }
    return output;
}

long btol(const string& n) {
    long output = 0;
    for (int i = 0; i < 36; i++) {
        if (n[35 - i] == '1') output += static_cast<long>(pow(2, i));
    }
    return output;
}

void overwrite(string& n, const string& mask) {
    for (int i = 0; i < mask.size(); i++) if (mask[i] != 'X') n[i] = mask[i];
}

vector<string> overwrite_mem(string& n, const string& mask) {
    vector<string> output = {""};
    for (int i = 0; i < mask.size(); i++) {
        vector<string> output_new;
        if (mask[i] == '0') for (string& s : output) output_new.push_back(s + n[i]);
        if (mask[i] == '1') for (string& s : output) output_new.push_back(s + '1');
        if (mask[i] == 'X') for (string& s : output) {output_new.push_back(s + '1'); output_new.push_back(s + '0'); }
        output = output_new;
    }

    return output;
}

void Day14::execute(const vector<string> &lines) {
    long part_1 = 0, part_2 = 0;
    string mask;
    map<long, long> bits, bits_2;

    for (const auto &line: lines) {
        if (line.substr(0, 4) == "mask") { mask = line.substr(7, line.size()-7); continue; }

        stringstream ss(line); string token; vector<string> string_line;
        while (getline(ss, token, ' ')) string_line.push_back(token);

        long index = stol(string_line[0].substr(4,string_line[0].size() - 5)); string index_s = ltob(index);
        long num_l = stol(string_line[2]); string num_s = ltob(num_l);

        vector<string> index_x = overwrite_mem(index_s, mask);
        for (const string& i : index_x) bits_2[btol(i)] = num_l;

        overwrite(num_s, mask);
        num_l = btol(num_s);

        bits[index] = num_l;
    }

    for (const auto [index, bit] : bits) part_1 += bit;
    for (const auto [index, bit] : bits_2) part_2 += bit;

    cout << "Part 1: " << part_1 << endl << "Part 2: " << part_2 << endl;
}
