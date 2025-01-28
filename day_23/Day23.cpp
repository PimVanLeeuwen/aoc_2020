#include "Day23.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

struct Cup {
    int value;
    Cup* next_cup;
    Cup* prev_cup;
};

void Day23::execute(const vector<string> &lines) {
    const string cups_input = "589174263";
    const auto start = new Cup();
    start->value = cups_input[0] - '0';

    Cup* current = start;
    for (int i = 1; i < cups_input.size(); i++) {
        Cup* new_cup = new Cup();
        new_cup->value = cups_input[i] - '0';
        new_cup->prev_cup = current;
        current->next_cup = new_cup;
        current = new_cup;
    }

    current->next_cup = start;
    start->prev_cup = current;

    current = start;

    for (int i = 0; i < 100; i++) {
        // remove the next three cups
        Cup* c1 = current->next_cup;
        const Cup* c2 = c1->next_cup;
        Cup* c3 = c2->next_cup;

        Cup* c4 = c3->next_cup;
        // tie the list together again
        current->next_cup = c4;
        c4->prev_cup = current;

        int destination_cup_val = current->value-1;
        Cup* destination_cup = current->next_cup;

        while (true) {
            // cout << destination_cup_val << endl;
            destination_cup = current->next_cup;
            bool cup_found = false;
            while (true) {
                if (destination_cup->value == destination_cup_val) {
                    cup_found = true;
                    break;
                }
                destination_cup = destination_cup->next_cup;
                if (destination_cup->value == current->value) break;
            }

            if (cup_found) break;

            if (destination_cup_val == 0) destination_cup_val = 10;
            else destination_cup_val--;
        }

        c3->next_cup = destination_cup->next_cup;
        destination_cup->next_cup->prev_cup = c3;

        destination_cup->next_cup = c1;
        c1->prev_cup = destination_cup;

        current = current->next_cup;
    }

    while (current->value != 1) current = current->next_cup;

    cout << "Part 1: ";
    for (int i = 0; i < 8; i++) {
        current = current->next_cup;
        cout << current->value;
    }
    cout << endl;

    const auto start_2 = new Cup();
    start_2->value = cups_input[0] - '0';

    Cup* current_2 = start_2;
    for (int i = 1; i < 1000000; i++) {
        Cup* new_cup = new Cup();
        if (i < cups_input.size()) {
            new_cup->value = cups_input[i] - '0';
        } else {
            new_cup->value = i + 1;
        }
        new_cup->prev_cup = current_2;
        current_2->next_cup = new_cup;
        current_2 = new_cup;
    }

    current_2->next_cup = start_2;
    start_2->prev_cup = current_2;

    current_2 = start_2;

    for (int i = 0; i < 10000000; i++) {
        if (i % 10000 == 0) {
            cout << i << endl;
        }
        // remove the next three cups
        Cup* c1 = current_2->next_cup;
        const Cup* c2 = c1->next_cup;
        Cup* c3 = c2->next_cup;

        Cup* c4 = c3->next_cup;
        // tie the list together again
        current_2->next_cup = c4;
        c4->prev_cup = current_2;

        int destination_cup_val = current_2->value-1;
        Cup* destination_cup = current_2->next_cup;

        while (true) {
            destination_cup = current_2->next_cup;
            bool cup_found = false;
            while (true) {
                if (destination_cup->value == destination_cup_val) {
                    cup_found = true;
                    break;
                }
                destination_cup = destination_cup->next_cup;
                if (destination_cup->value == current_2->value) break;
            }

            if (cup_found) break;

            if (destination_cup_val == 0) destination_cup_val = 1000000;
            else destination_cup_val--;
        }

        c3->next_cup = destination_cup->next_cup;
        destination_cup->next_cup->prev_cup = c3;

        destination_cup->next_cup = c1;
        c1->prev_cup = destination_cup;

        current_2 = current_2->next_cup;
    }

    while (current_2->value != 1) current_2 = current_2->next_cup;

    cout << "Part 2: " << current_2->next_cup->value*current_2->next_cup->next_cup->value << endl;
}
