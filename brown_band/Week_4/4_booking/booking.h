
namespace RAII {
    template<typename Provider>
    class Booking {
    public:
        using BookingId = typename Provider::BookingId;
        Booking(Provider* provider,  const BookingId& id):provider(provider), id(id) {}
        Booking(const Booking&)  = delete;
        Booking(Booking&& other):provider(other.provider), id(other.id) {
            other.provider = nullptr;
        }
        Booking& operator=(const Booking&) = delete;
        Booking& operator=(Booking&& other) {
            provider = other.provider;
            id = other.id;
            other.provider = nullptr;
            return *this;
        }
        BookingId GetId() const{
            return id;
        }
        ~Booking() {
            if (provider!= nullptr) {
                provider->CancelOrComplete(*this);
            }
        }
    private:
        Provider* provider;
        BookingId id;
    };
}