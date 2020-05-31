#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<string> s;
    string c, x;
    cin >> x;
    int n;
    cin >> n;
    s.push_back(x);
    string prev = "*";
    for (int i = 0; i < n; i++) {
        cin >> c >> x;
        if (((prev == "+") || (prev == "-")) && ((c == "*") || (c == "/"))) {
            s.push_back("(");
            s.push_front(")");
        }
        s.push_front(" " + c + " " + x);
        prev = c;
    }
    while (!s.empty()) {
        cout << s.back();
        s.pop_back();
    }
    return 0;
}
