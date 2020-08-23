#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

// Реализуйте этот класс
class Database {
public:
    bool Put(const Record &record) {
        string id = record.id;
        if (idRecord.find(id) != end(idRecord)) {
            return false;
        }
        idRecord.insert({id, {record, end(userRecord), end(timeRecord), end(karmaRecord)}});
        idRecord[id].userIter = userRecord.insert({record.user, &idRecord[id].record});
        idRecord[id].timeIter = timeRecord.insert({record.timestamp, &idRecord[id].record});
        idRecord[id].karmaIter = karmaRecord.insert({record.karma, &idRecord[id].record});
        return true;

    }

    const Record *GetById(const string &id) const {
        if (idRecord.find(id) == end(idRecord)) {
            return nullptr;
        }
        return &idRecord.at(id).record;
    }

    bool Erase(const string &id) {
        auto it = idRecord.find(id);
        if (it == end(idRecord)) {
            return false;
        }
        userRecord.erase(it->second.userIter);
        karmaRecord.erase(it->second.karmaIter);
        timeRecord.erase(it->second.timeIter);
        idRecord.erase(it);
        return true;
    }

    template<typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        auto first = timeRecord.lower_bound(low);
        auto last = timeRecord.upper_bound(high);
        for (; first != last; first++) {
            if (!callback(*first->second)) {
                return;
            }
        }
    }

    template<typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        auto first = karmaRecord.lower_bound(low);
        auto last = karmaRecord.upper_bound(high);
        for (; first != last; first++) {
            if (!callback(*first->second)) {
                return;
            }
        }
    }

    template<typename Callback>
    void AllByUser(const string &user, Callback callback) const {
        auto p = userRecord.equal_range(user);
        for (; p.first != p.second; p.first++) {
            if (!callback(*p.first->second)) {
                return;
            }
        }
    }

private:
    struct Data {
        Record record;
        multimap<string, Record *>::iterator userIter;
        multimap<int, Record *>::iterator timeIter;
        multimap<int, Record *>::iterator karmaIter;
    };
    map<string, Data> idRecord;
    multimap<string, Record *> userRecord;
    multimap<int, Record *> timeRecord;
    multimap<int, Record *> karmaRecord;
};

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record &) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestSameUser() {
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record &) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}
