#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

template<typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
            : first(begin), last(end) {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

private:
    Iterator first, last;
};

template<typename Collection>
auto Head(Collection &v, size_t top) {
    return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
    string name;
    int age, income;
    bool is_male;
};

vector<Person> ReadPeople(istream &input) {
    int count;
    input >> count;

    vector<Person> result(count);
    for (Person &p : result) {
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
    }
    sort(begin(result), end(result), [](const Person &lhs, const Person &rhs) {
        return lhs.age < rhs.age;
    });
    return result;
}


class People {
public:
    explicit People(vector<Person> people) {
        by_age = [&people]() {
            sort(begin(people), end(people), [](const Person &lhs, const Person &rhs) {
                return lhs.age < rhs.age;
            });
            return people;
        }();
        wealth_prefix = [&people]() {
            sort(begin(people), end(people), [](const Person &lhs, const Person &rhs) {
                return lhs.income > rhs.income;
            });
            vector<uint64_t> ans(people.size());
            ans[0] = people[0].income;
            for (int i = 1; i < ans.size(); i++) {
                ans[i] = ans[i - 1] + people[i].income;
            }
            return ans;
        }();
        by_sex = [&people]() {
            sort(begin(people), end(people), [](const Person &lhs, const Person &rhs) {
                return lhs.is_male < rhs.is_male;
            });
            auto first_male = lower_bound(begin(people), end(people), true, [](const Person &lhs, bool gender) {
                return lhs.is_male < gender;
            });
            sort(begin(people), first_male, [](const Person &lhs, const Person &rhs) {
                return lhs.name < rhs.name;
            });
            sort(first_male, end(people), [](const Person &lhs, const Person &rhs) {
                return lhs.name < rhs.name;
            });
            return people;
        }();
        mostM = "";
        mostW = "";
    }

    void Age() const {
        int adult_age;
        cin >> adult_age;

        auto adult_begin = lower_bound(
                begin(by_age), end(by_age), adult_age, [](const Person &lhs, int age) {
                    return lhs.age < age;
                }
        );

        cout << "There are " << std::distance(adult_begin, end(by_age))
             << " adult people for maturity age " << adult_age << '\n';
    }

    void Wealthy() const {
        int count;
        cin >> count;
        cout << "Top-" << count << " people have total income " << wealth_prefix[count - 1] << '\n';
    }

    void PopularName() {
        char gender;
        cin >> gender;
        if ((gender == 'W') && (!mostW.empty())) {
            cout << "Most popular name among people of gender " << gender << " is "
                 << mostW << '\n';
            return;
        } else if ((gender == 'M') && (!mostM.empty())) {
            cout << "Most popular name among people of gender " << gender << " is "
                 << mostM << '\n';
            return;
        }
        auto first_male = lower_bound(begin(by_sex), end(by_sex), true, [](const Person &lhs, bool gender) {
            return lhs.is_male < gender;
        });
        IteratorRange range = IteratorRange(begin(by_sex), end(by_sex));
        if (gender == 'W') {
            range = IteratorRange(begin(by_sex), first_male);
        } else {
            range = IteratorRange(first_male, end(by_sex));
        }
        if (range.begin() == range.end()) {
            cout << "No people of gender " << gender << '\n';
        } else {
            const string *most_popular_name = &range.begin()->name;
            int count = 1;
            for (auto i = range.begin(); i != range.end();) {
                auto same_name_end = find_if_not(i, range.end(), [i](const Person &p) {
                    return p.name == i->name;
                });
                auto cur_name_count = std::distance(i, same_name_end);
                if (cur_name_count > count) {
                    count = cur_name_count;
                    most_popular_name = &i->name;
                }
                i = same_name_end;
            }
            cout << "Most popular name among people of gender " << gender << " is "
                 << *most_popular_name << '\n';
            if (gender == 'W') {
                mostW = *most_popular_name;
            } else {
                mostM = *most_popular_name;
            }
        }
    }

private:
    vector<Person> by_age;
    vector<uint64_t> wealth_prefix;
    vector<Person> by_sex;
    string mostW;
    string mostM;
};

int main() {
    People people(ReadPeople(cin));
    for (string command; cin >> command;) {
        if (command == "AGE") {
            people.Age();
        } else if (command == "WEALTHY") {
            people.Wealthy();
        } else if (command == "POPULAR_NAME") {
            people.PopularName();
        }
    }
}