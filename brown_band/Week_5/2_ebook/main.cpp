#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
            : user_last_page(MAX_USER_COUNT_ + 1, -1), page_counter(MAX_PAGE_COUNT_, 0) {}

    void Read(int user_id, int page_count) {
        UpdatePageRange(user_last_page[user_id] + 1, page_count + 1);
        user_last_page[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        if (user_last_page[user_id] == -1) {
            return 0;
        }
        int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }
        return (user_count - page_counter[user_last_page[user_id]]) * 1.0 / (user_count - 1);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1000;

    vector<int> user_last_page;
    vector<int> page_counter;

    int GetUserCount() const {
        return page_counter[0];
    }

    void UpdatePageRange(int lhs, int rhs) {
        for (int i = lhs; i < rhs; ++i) {
            ++page_counter[i];
        }
    }
};


int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}