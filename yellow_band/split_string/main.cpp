#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string &s) {
    vector<string> ans;
    auto it = find(s.begin(), s.end(), ' ');
    auto prev = s.begin();
    while (it != s.end()) {
        ans.emplace_back(string(prev, it));
        it++;
        prev = it;
        it = find(prev, s.end(), ' ');
    }
    ans.emplace_back(string(prev, it));
    return ans;
}

/*int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}*/