#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <list>
using namespace std;


bool IsSubdomain(string_view subdomain, string_view domain) {
    int i = 0;
    int j = 0;
    while ((i < subdomain.size()) && (j < domain.size())) {
        if (subdomain[i++] != domain[j++]) {
            return false;
        }
    }
    return (i == subdomain.size()) && ((j == domain.size()) || (domain[j] == '.'));
}


list<string> ReadDomains() {
    size_t count;
    cin >> count;

    list<string> domains;
    for (size_t i = 0; i < count; ++i) {
        string domain;
        cin >> domain;
        domains.push_back(domain);
    }
    return domains;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    list<string> banned_domains = ReadDomains();
    list<string> domains_to_check = ReadDomains();

    for (string &domain : banned_domains) {
        reverse(begin(domain), end(domain));
    }
    banned_domains.sort();
    for (auto it = begin(banned_domains); next(it)!=end(banned_domains); it++) {
        if (IsSubdomain(*it, *next(it))) {
            banned_domains.erase(next(it));
            it--;
        }
    }

    for (string &domain : domains_to_check) {
        reverse(begin(domain), end(domain));
        auto it = upper_bound(begin(banned_domains), end(banned_domains), domain);
        if ((it == begin(banned_domains)) || (!IsSubdomain(*prev(it), domain))) {
            cout << "Good\n";
        } else {
            cout << "Bad\n";
        }
    }
    return 0;
}