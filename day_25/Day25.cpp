#include "Day25.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

long transform(const long value, const long subject_nr) {
    return value * subject_nr % 20201227;
}

void Day25::execute(const vector<string> &lines) {
    const pair<long, long> pk = {9232416, 14144084};
    tuple<long, long, long> n_pk = {1, 1, 1};
    pair<long, long> loop = {0, 0};

    constexpr long subject = 7;

    while (get<0>(n_pk) != pk.first) {
        get<0>(n_pk) = transform(get<0>(n_pk), subject);
        loop.first++;
    }

    while (get<1>(n_pk) != pk.second) {
        get<1>(n_pk) = transform(get<1>(n_pk), subject);
        loop.second++;
    }

    for (long i = 0; i < loop.first; i++) {
        get<2>(n_pk) = transform(get<1>(n_pk), get<2>(n_pk));
    }

    cout << "Part 1: " << get<2>(n_pk);
}
