#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
#include <functional>

using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats &other) {
        for (const auto &p: other.word_frequences) {
            this->word_frequences[p.first] += p.second;
        }
    }
};

Stats ExploreLine(const set<string> &key_words, const string &line) {
    string buf;
    stringstream tokenizer(line);
    Stats ans;
    while (tokenizer >> buf) {
        if (key_words.find(buf) != end(key_words)) {
            ans.word_frequences[buf]++;
        }
    }
    return ans;
}

Stats ExploreKeyWordsSingleThread(
        const set<string> &key_words, const vector<string> &lines, size_t first_line, size_t page_size
) {
    Stats result;
    for (int i = first_line; i < min(first_line + page_size, lines.size()); i++) {
        result += ExploreLine(key_words, lines[i]);
    }
    return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input) {
    Stats result;
    vector<future<Stats> > futures;
    vector<string> lines;

    for (string line; getline(input, line);) {
        lines.push_back(line);
    }
    size_t first_line = 0;
    size_t sz = lines.size();
    size_t page_size = (sz / 4) + (sz % 4);
    while (first_line < sz) {
        futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(lines), first_line, page_size));
        first_line += page_size;
    }
    for (auto &f:futures) {
        result += f.get();
    }
    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 6},
            {"rocks",  2},
            {"sucks",  1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
