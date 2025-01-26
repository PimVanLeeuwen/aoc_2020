#include "Day21.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <sstream>

using namespace std;

set<string> intersect(const set<string>& a, const set<string>& b) {
    set<string> output;
    for (const string& i : a) {
        if (b.find(i) != b.end()) output.insert(i);
    }
    return output;
}

void Day21::execute(const vector<string> &lines) {
    long part_1 = 0;
    vector<pair<set<string>, set<string>>> food_list;
    set<string> all_allergens;
    set<string> all_ingredients;
    deque<string> process_allergens;
    map<string, string> map_allergens;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line); string token;
        bool ingredients_adding = true;
        set<string> ingredients;
        set<string> allergens;

        // separate line
        while (getline(ss, token, ' ')) {
            if (ingredients_adding && token[0] != '(') {
                ingredients.insert(token);
                all_ingredients.insert(token);
            } else if (token[0] == '(') {
                ingredients_adding = false;
            } else {
                allergens.insert(token.substr(0,token.size()-1));
                all_allergens.insert(token.substr(0,token.size()-1));
            }
        }

        food_list.emplace_back(ingredients, allergens);
    }

    for (const string& a : all_allergens) process_allergens.push_back(a);

    while (!process_allergens.empty()) {
        string current_allergen = process_allergens.front(); process_allergens.pop_front();
        set<string> ingredients_subset = all_ingredients;

        for (const auto& [in, al] : food_list) {
            if (al.find(current_allergen) != al.end()) {
                ingredients_subset = intersect(ingredients_subset, in);
            }
        }

        set<string> new_ingredients_subset;
        for (const string& i : ingredients_subset) {
            if (map_allergens.find(i) == map_allergens.end()) new_ingredients_subset.insert(i);
        }
        ingredients_subset = new_ingredients_subset;

        if (ingredients_subset.size() == 1) {
            string ingredient;
            for (string s : ingredients_subset) ingredient = s;
            map_allergens[ingredient] = current_allergen;
        } else {
            process_allergens.push_back(current_allergen);
        }
    }

    for (const auto& [in, al] : food_list) {
        for (const string& i : in) {
            if (map_allergens.find(i) == map_allergens.end()) part_1++;
        }
    }

    set<pair<string, string>> dangerous_ingredients;
    for (const auto& [in, al] : map_allergens) {
        dangerous_ingredients.emplace(al, in);
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: ";
    for (const auto& [al, in] : dangerous_ingredients) cout << in << ',';
}
