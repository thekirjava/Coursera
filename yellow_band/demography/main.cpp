#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintStats(vector<Person> persons) {
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << '\n';
    vector<Person> female;
    vector<Person> male;
    partition_copy(persons.begin(), persons.end(), back_inserter(female), back_inserter(male), [](const Person &p) {
        return p.gender == Gender::FEMALE;
    });
    cout << "Median age for females = " << ComputeMedianAge(female.begin(), female.end()) << '\n';
    cout << "Median age for males = " << ComputeMedianAge(male.begin(), male.end()) << '\n';
    auto female_it = partition(female.begin(), female.end(), [](const Person &p) {
        return p.is_employed;
    });
    auto male_it = partition(male.begin(), male.end(), [](const Person &p) {
        return p.is_employed;
    });
    cout << "Median age for employed females = " << ComputeMedianAge(female.begin(), female_it) << '\n';
    cout << "Median age for unemployed females = " << ComputeMedianAge(female_it, female.end()) << '\n';
    cout << "Median age for employed males = " << ComputeMedianAge(male.begin(), male_it) << '\n';
    cout << "Median age for unemployed males = " << ComputeMedianAge(male_it, male.end()) << '\n';
}
