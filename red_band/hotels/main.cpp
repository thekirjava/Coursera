#include <iostream>
#include <map>
#include <string>
#include <deque>
#include <map>
#include "profile.h"
using namespace std;
struct client {
    int64_t time;
    int rooms;
    int id;
};
struct hotel_info {
    deque<client> requests;
    map<int, int> clients;
    int total_rooms = 0;
    int total_clients = 0;
};

class booking_system {
public:
    booking_system() : hotels(), total_time(-1e18) {}

    void book(const int64_t &time, const string &hotel, const int &client_id, const int &room_count) {
       // LOG_DURATION("book")
        total_time = time;
        if (hotels[hotel].clients[client_id] == 0) {
            hotels[hotel].total_clients++;
        }
        hotels[hotel].clients[client_id]++;
        hotels[hotel].requests.push_back({time, room_count, client_id});
        hotels[hotel].total_rooms += room_count;
    };


    int count_clients(const string &hotel) {
        update(hotel);
        return hotels[hotel].total_clients;
    }

    int count_rooms(const string &hotel) {
        update(hotel);
        return hotels[hotel].total_rooms;
    }

private:

    map<string, hotel_info> hotels;
    int64_t total_time;

    void update(const string &hotel) {
        while ((!hotels[hotel].requests.empty()) && (hotels[hotel].requests.front().time + 86400 <= total_time)) {
            hotels[hotel].total_rooms -= hotels[hotel].requests.front().rooms;
            hotels[hotel].clients[hotels[hotel].requests.front().id]--;
            if (hotels[hotel].clients[hotels[hotel].requests.front().id] == 0) {
                hotels[hotel].total_clients--;
            }
            hotels[hotel].requests.pop_front();
        }
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int32_t q;
    cin >> q;
    booking_system bookingSystem;
    for (size_t i = 0; i < q; i++) {
        string command;
        cin >> command;
        if (command == "BOOK") {
            int64_t time;
            string hotel;
            int client, rooms;
            cin >> time >> hotel >> client >> rooms;
            bookingSystem.book(time, hotel, client, rooms);
        } else {
            string hotel;
            cin >> hotel;
            if (command == "CLIENTS") {
                cout << bookingSystem.count_clients(hotel) << '\n';
            } else {
                cout << bookingSystem.count_rooms(hotel) << '\n';
            }
        }
    }
    return 0;
}
