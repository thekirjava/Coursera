#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
    vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));
    auto first_triplet = (elements.end() - elements.begin()) / 3 + elements.begin();
    auto second_triplet = (elements.end() - elements.begin()) * 2 / 3 + elements.begin();
    MergeSort(elements.begin(), first_triplet);
    MergeSort(first_triplet, second_triplet);
    MergeSort(second_triplet, elements.end());
    vector<typename RandomIt::value_type> temp;
    merge(make_move_iterator(elements.begin()), make_move_iterator(first_triplet),
            make_move_iterator(first_triplet), make_move_iterator(second_triplet), back_inserter(temp));
    merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()),
            make_move_iterator(second_triplet), make_move_iterator(elements.end()), range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
