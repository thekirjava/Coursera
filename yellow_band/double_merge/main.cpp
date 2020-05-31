#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto mid = (elements.end() - elements.begin()) / 2 + elements.begin();
    MergeSort(elements.begin(), mid);
    MergeSort(mid, elements.end());
    merge(elements.begin(), mid, mid, elements.end(), range_begin);
}

