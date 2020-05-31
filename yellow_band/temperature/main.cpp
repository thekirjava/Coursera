#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    std::vector<int64_t> t(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> t[i];
    }
    int64_t avg = 0;
    for (auto i:t) {
        avg += i;
    }
    avg /= static_cast<int64_t>(t.size());
    int64_t ans = 0;
    for (auto i:t) {
        if (i > avg) {
            ans++;
        }
    }
    std::cout << ans << '\n';
    for (int i = 0; i < N; ++i) {
        if (t[i] > avg) {
            std::cout << i << " ";
        }
    }
    return 0;
}
