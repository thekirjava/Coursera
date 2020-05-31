#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    uint64_t R;
    std::cin>>R;
    uint64_t ans = 0;
    for (int i = 0; i < N; i++) {
        uint64_t W, H, D;
        std::cin >> W >> H >> D;
        ans += R * W * H * D;
    }
    std::cout << ans;
    return 0;
}
