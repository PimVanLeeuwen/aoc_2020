#include "Day24.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <sstream>

using namespace std;

void Day24::execute(const vector<string> &lines) {
    long part_1 = 0, part_2 = 0;
    vector tiles_grid(400, vector(400, false));

    set<pair<int, int>> tiles_flipped;

    for (const auto &line: lines) {
        pair<int, int> tile = {200,200};
        int i = 0;
        while (i < line.size()) {
            if (line[i] == 'e') {
                tile.first++;
                i++;
            } else if (line[i] == 'w') {
                tile.first--;
                i++;
            } else if (line[i] == 's' && line[i + 1] == 'w') {
                tile.first--;
                tile.second++;
                i += 2;
            } else if (line[i] == 'n' && line[i + 1] == 'e') {
                tile.first++;
                tile.second--;
                i += 2;
            } else if (line[i] == 's' && line[i + 1] == 'e') {
                tile.second++;
                i += 2;
            } else if (line[i] == 'n' && line[i + 1] == 'w') {
                tile.second--;
                i += 2;
            }
        }
        tiles_grid[tile.second][tile.first] = tiles_grid[tile.second][tile.first] ? false : true;
    }

    for (int y = 0; y < tiles_grid.size(); y++) {
        for (int x = 0; x < tiles_grid.size(); x++) {
            if (tiles_grid[y][x]) part_1++;
        }
    }

    for (int d = 0; d < 100; d++) {
        vector tiles_grid_new(400, vector(400, false));
        for (int y = 1; y < tiles_grid.size() - 1; y++) {
            for (int x = 1; x < tiles_grid.size() - 1; x++) {
                cout << "test"; // TODO finish this
            }
        }
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
