#include "Day16.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <sstream>

using namespace std;

void Day16::execute(const vector<string> &lines) {
    long part_1 = 0, part_2 = 1;
    map<string, tuple<int, int, int, int>> fields;
    vector<int> my_ticket;
    set<vector<int>> nearby_tickets;
    set<vector<int>> nearby_valid_tickets;

    for (const auto &line: lines) {
        if (line.find(" or ") != string::npos) {
            string name = line.substr(0, line.find(':'));
            string info = line.substr(line.find(':') + 2); stringstream ss(info); string token;

            vector<string> info_vec; while (getline(ss, token, ' ')) info_vec.push_back(token);

            int start_1 = stoi(info_vec[0].substr(0, info_vec[0].find('-')));
            int end_1 = stoi(info_vec[0].substr(info_vec[0].find('-') +1 ));
            int start_2 = stoi(info_vec[2].substr(0, info_vec[2].find('-')));
            int end_2 = stoi(info_vec[2].substr(info_vec[2].find('-') +1 ));

            fields[name] = {start_1, end_1, start_2, end_2};
        } else if (line.find(',') != string::npos) {
            stringstream ss(line); string token;
            vector<int> ticket; while (getline(ss, token, ',')) ticket.push_back(stoi(token));
            if (my_ticket.empty()) my_ticket = ticket;
            else nearby_tickets.insert(ticket);
        }
    }

    vector valid_fields(my_ticket.size(), set<string>());
    vector<string> valid_fields_strings(my_ticket.size(), "");
    for (auto & valid_field : valid_fields) for (const auto&[f_name, _c] : fields) valid_field.insert(f_name);

    for (const vector<int>& ticket : nearby_tickets) {
        bool ticket_valid = true;
        for (int t : ticket) {
            bool valid = false;
            for (const auto&[f_name, content] : fields) {
                if (t >= get<0>(content) && t <= get<1>(content) || t >= get<2>(content) && t <= get<3>(content)) {valid = true; break;}
            }
            if (!valid) {part_1 += t; ticket_valid = false;}
        }
        if (ticket_valid) nearby_valid_tickets.insert(ticket);
    }

    for (const vector<int>& ticket : nearby_valid_tickets) {
        for (int i = 0; i < ticket.size(); i++) {
            set<string> valid_fields_local;
            for (const auto&[f_name, content] : fields) {
                if ((ticket[i] >= get<0>(content) && ticket[i] <= get<1>(content) ||
                    ticket[i] >= get<2>(content) && ticket[i] <= get<3>(content)) &&
                    valid_fields[i].find(f_name) != valid_fields[i].end()) valid_fields_local.insert(f_name);
            }
            valid_fields[i] = valid_fields_local;
        }
    }

    while (true) {
        bool op_done = false;
        for (int i = 0; i < valid_fields.size(); i++) {
            if (valid_fields[i].size() == 1) for (const string& s : valid_fields[i]) {valid_fields_strings[i] = s; break;}
            else {
                op_done = true;
                set<string> new_set;
                for (const auto s : valid_fields[i]) {
                    if (find(valid_fields_strings.begin(), valid_fields_strings.end(), s) == valid_fields_strings.end()) new_set.insert(s);
                }
                valid_fields[i] = new_set;
            }
        }

        if (!op_done) break;
    }

    for (int i = 0; i < my_ticket.size(); i++) {
        if (valid_fields_strings[i].find("departure") != string::npos) part_2 *= my_ticket[i];
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
