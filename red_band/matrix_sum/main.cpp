#include "test_runner.h"
#include <vector>
#include <future>

using namespace std;


int64_t CalculateMatrixSum(const vector<vector<int>> &matrix, size_t first_row, size_t page_size) {
    int64_t ans = 0;
    for (size_t i = first_row; i < min(first_row + page_size, matrix.size()); i++) {
        for (int j : matrix[i]) {
            ans += j;
        }
    }
    return ans;
}

int64_t CalculateMatrixSum(const vector<vector<int>> &matrix) {
    size_t sz = matrix.size();
    size_t page_size = (sz / 4) + (sz % 4);

    size_t first_row = 0;
    vector<future<int64_t> > futures;
    while (first_row < sz) {
        futures.push_back(async([&matrix, first_row, page_size] {
            return CalculateMatrixSum(matrix, first_row, page_size);
        }));
        first_row += page_size;
    }
    int64_t ans = 0;
    for (auto &f: futures) {
        ans += f.get();
    }
    return ans;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9,  10, 11, 12},
            {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
