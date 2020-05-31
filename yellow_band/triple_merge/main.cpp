#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 3) {
        return;
    }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto first_triplet = (elements.end() - elements.begin()) / 3 + elements.begin();
    auto second_triplet = (elements.end() - elements.begin()) * 2 / 3 + elements.begin();
    MergeSort(elements.begin(), first_triplet);
    MergeSort(first_triplet, second_triplet);
    MergeSort(second_triplet, elements.end());
    vector<typename RandomIt::value_type> temp;
    merge(elements.begin(), first_triplet, first_triplet, second_triplet, back_inserter(temp));
    merge(temp.begin(), temp.end(), second_triplet, elements.end(), range_begin);
}

