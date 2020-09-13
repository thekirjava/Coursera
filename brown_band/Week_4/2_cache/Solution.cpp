#include <utility>
#include <unordered_map>
#include <list>
#include <mutex>

#include "Common.h"

using namespace std;

class LruCache : public ICache {
public:
    LruCache(
            shared_ptr<IBooksUnpacker> books_unpacker,
            const Settings &settings
    ) : books_unpacker(move(books_unpacker)), settings(settings) {
        memory = 0;
    }

    BookPtr GetBook(const string &book_name) override {
        std::lock_guard<std::mutex> guard(mutex);
        auto it = cache_finder.find(book_name);
        if (it == end(cache_finder)) {
            BookPtr book = books_unpacker->UnpackBook(book_name);
            memory += book->GetContent().size();
            cache.push_front(book);
            cache_finder.insert({book_name, begin(cache)});
            while ((memory > settings.max_memory) && (!cache.empty())) {
                memory -= cache.back()->GetContent().size();
                cache_finder.erase(cache.back()->GetName());
                cache.pop_back();
            }
            if (cache.empty()) {
                return book;
            }
            return cache.front();
        } else {
            auto cache_it = it->second;
            cache.splice(begin(cache), cache, cache_it);
            return *cache_it;
        }

    }

private:
    shared_ptr<IBooksUnpacker> books_unpacker;
    Settings settings;
    list<BookPtr> cache;
    unordered_map<string, list<BookPtr>::iterator> cache_finder;
    int memory;
    std::mutex mutex;
};


unique_ptr<ICache> MakeCache(
        shared_ptr<IBooksUnpacker> books_unpacker,
        const ICache::Settings &settings
) {
    return make_unique<LruCache>(move(books_unpacker), settings);
}
