#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int64_t a, b;
    cin >> a >> b;
    uint64_t dist = b > 0 ? INT64_MAX - a : a - INT64_MIN;
    if (dist >= abs(b)) {
        cout << a + b;
    } else {
        cout << "Overflow!";
    }
    return 0;
}
