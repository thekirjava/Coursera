#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int> &numbers) {
    auto negative = find_if(numbers.begin(), numbers.end(), [](const int& x) { return x < 0; });
    while (negative != numbers.begin()) {
        negative--;
        cout << *negative << " ";
    }
}


/*int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}*/
