#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
            : users(), pages(1001), user_page(100001) {}

    void Read(int user_id, int page_count) {
        if (page_count != 0) {
            users.insert(user_id);
            pages[user_page[user_id]].erase(user_id);
            pages[page_count].insert(user_id);
            user_page[user_id] = page_count;
        }
    }

    double Cheer(int user_id) const {
        if (user_page[user_id] == 0) {
            return 0;
        }
        if (users.size() == 1) {
            return 1;
        }
        double counter = 0;
        for (int i = 1; i < user_page[user_id]; ++i) {
            counter += pages[i].size();
        }
        return counter / (users.size() - 1);
    }

private:
    set<int> users;
    vector<set<int> > pages;
    vector<int> user_page;
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