#include "test_runner.h"
#include <vector>

using namespace std;

template<typename T>
class Table {
public:
    Table(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data.assign(rows, vector<T>(cols));
    }

    vector<T> &operator[](size_t i) {
        return data[i];
    }

    vector<T> operator[](size_t i) const {
        return data[i];
    }

    void Resize(size_t N, size_t M) {
        data.resize(N);
        for (int i = 0; i < N; i++) {
            data[i].resize(M);
        }
        rows = N;
        cols = M;
    }

    pair<size_t, size_t> Size() const {
        return {rows, cols};
    }

private:
    vector<vector<T> > data;
    size_t rows;
    size_t cols;

};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
