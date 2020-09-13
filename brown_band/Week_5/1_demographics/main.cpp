#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintStats(vector<Person> persons) {
    auto gender_border = partition(begin(persons), end(persons),
                                   [](const Person &p) { return p.gender == Gender::FEMALE; });
    auto female_border = partition(begin(persons), gender_border, [](const Person &p) { return p.is_employed; });
    auto male_border = partition(gender_border, end(persons), [](const Person &p) { return p.is_employed; });
    cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << '\n';
    cout << "Median age for females = " << ComputeMedianAge(begin(persons), gender_border) << '\n';
    cout << "Median age for males = " << ComputeMedianAge(gender_border, end(persons)) << '\n';
    cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), female_border) << '\n';
    cout << "Median age for unemployed females = " << ComputeMedianAge(female_border, gender_border) << '\n';
    cout << "Median age for employed males = " << ComputeMedianAge(gender_border, male_border) << '\n';
    cout << "Median age for unemployed males = " << ComputeMedianAge(male_border, end(persons)) << '\n';
}

