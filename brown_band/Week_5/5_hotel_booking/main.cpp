#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

class HotelManager {
public:
    void Book(int64_t time, const string &hotel_name, int client_id, int room_count) {
        current_time = time;
        hotels[hotel_name].Book({time, client_id, room_count});
    }

    int GetRoomsByDay(const string &hotel_name) {
        return hotels[hotel_name].GetRoomsByDay(current_time);
    }

    int GetClientsByDay(const string &hotel_name) {
        return hotels[hotel_name].GetClientsByDay(current_time);
    }

private:
    struct Booking {
        int64_t time;
        int client_id;
        int room_count;
    };

    class Hotel {
    public:
        void Book(const Booking &book) {
            last_bookings.push(book);
            room_count += book.room_count;
            clients[book.client_id]++;

        }

        int GetRoomsByDay(int64_t current_time) {
            RemoveOldBooking(current_time);
            return room_count;
        }

        int GetClientsByDay(int64_t current_time) {
            RemoveOldBooking(current_time);
            return clients.size();
        }

    private:
        void RemoveOldBooking(int64_t current_time) {
            while ((!last_bookings.empty()) && (current_time - last_bookings.front().time >= 86400)) {
                PopBooking();
            }
        }

        void PopBooking() {
            Booking b = last_bookings.front();
            clients[b.client_id]--;
            if (clients[b.client_id] == 0) {
                clients.erase(b.client_id);
            }
            room_count -= b.room_count;
            last_bookings.pop();
        }

        queue<Booking> last_bookings;
        int room_count = 0;
        map<int, int> clients;
    };

    int64_t current_time = -1e18;
    map<string, Hotel> hotels;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    HotelManager hotelManager;
    for (int i = 0; i < T; i++) {
        string request;
        cin >> request;
        if (request == "BOOK") {
            int64_t time;
            string hotel_name;
            int client_id;
            int room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            hotelManager.Book(time, hotel_name, client_id, room_count);
        } else if (request == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotelManager.GetClientsByDay(hotel_name) << '\n';
        } else if (request == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotelManager.GetRoomsByDay(hotel_name) << '\n';
        }
    }
    return 0;
}
