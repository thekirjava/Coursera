#include "database.h"

void Database::Add(const Date &date, const string &event) {
    if (multi_event.count({date, event}) == 0) {
        this->db[date].push_back(event);
        multi_event.insert({date, event});
    }
}

void Database::Print(ostream &os) const {
    for (const auto &p:db) {
        for (int i = 0; i < p.second.size(); i++) {
            os << p.first << " " << p.second[i] << '\n';
        }
    }
}


string Database::Last(Date date) const {
    auto it = db.upper_bound(date);
    if (it == begin(db)) {
        return "No entries";
    } else {
        it--;
        while (it->second.empty()) {
            if (it == begin(db)) {
                return "No entries";
            }
            it--;
        }
        ostringstream os;
        os << it->first << " " << it->second.back();
        return os.str();
    }
}
