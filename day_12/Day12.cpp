#include "Day12.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

map<char, pair<int, int>> directions = {
{'E', {0,1}},
{'W', {0,-1}},
{'N', {-1,0}},
{'S', {1,0}},
};

void Day12::execute(const vector<string> &lines) {
    vector<vector<string>> matrix;

    tuple ship = {0, 0, 'E'};
    tuple ship_2 = {0, 0};
    tuple waypoint = {-1, 10};

    for (const auto &line: lines) {
        const int value = stoi(line.substr(1, line.size()-1));
        if (line[0] == 'F') {
            get<0>(ship) += directions[get<2>(ship)].first*value; get<1>(ship) += directions[get<2>(ship)].second*value;
            get<0>(ship_2) += get<0>(waypoint)*value; get<1>(ship_2) += get<1>(waypoint)*value;
        } else if (line[0] == 'L') {
            int turns = value/90;
            while (turns--) {
                if (get<2>(ship) == 'E') get<2>(ship) = 'N';
                else if (get<2>(ship) == 'N') get<2>(ship) = 'W';
                else if (get<2>(ship) == 'W') get<2>(ship) = 'S';
                else if (get<2>(ship) == 'S') get<2>(ship) = 'E';

                const int left = get<0>(waypoint);
                get<0>(waypoint) = get<1>(waypoint)*-1;
                get<1>(waypoint) = left;
            }
        } else if (line[0] == 'R') {
            int turns = value/90;
            while (turns--) {
                if (get<2>(ship) == 'E') get<2>(ship) = 'S';
                else if (get<2>(ship) == 'N') get<2>(ship) = 'E';
                else if (get<2>(ship) == 'W') get<2>(ship) = 'N';
                else if (get<2>(ship) == 'S') get<2>(ship) = 'W';

                const int left = get<0>(waypoint);
                get<0>(waypoint) = get<1>(waypoint);
                get<1>(waypoint) = -1*left;
            }
        }
        else if (line[0] == 'N') {get<0>(ship) -= value; get<0>(waypoint) -= value;}
        else if (line[0] == 'E') {get<1>(ship) += value; get<1>(waypoint) += value;}
        else if (line[0] == 'S') {get<0>(ship) += value; get<0>(waypoint) += value;}
        else if (line[0] == 'W') {get<1>(ship) -= value; get<1>(waypoint) -= value;}
    }


    cout << "Part 1: " << abs(get<0>(ship)) + abs(get<1>(ship)) << endl;
    cout << "Part 2: " << abs(get<0>(ship_2)) + abs(get<1>(ship_2)) << endl;
}
