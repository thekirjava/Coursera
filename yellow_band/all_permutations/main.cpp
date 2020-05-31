#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    int count = 1;
    std::vector<int> perm(N);
    for (int i = 0; i < N; i++) {
        count *= i + 1;
        perm[i] = N - i;
    }
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < N; j++) {
            cout << perm[j] << " ";
        }
        cout << '\n';
        prev_permutation(perm.begin(), perm.end());
    }
    return 0;
}
