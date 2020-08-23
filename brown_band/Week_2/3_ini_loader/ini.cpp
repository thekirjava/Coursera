#include "ini.h"

using namespace std;

namespace Ini {
    Section &Document::AddSection(string name) {
        sections.insert({name, Section()});
        return sections[name];
    }

    const Section &Document::GetSection(const string &name) const {
        return sections.at(name);
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }

    Document Load(istream &input) {
        Document document;
        string s;
        Section *curr;
        while (getline(input, s)) {
            if (s.empty()) {
                continue;
            }
            if ((s[0] == '[') && (s[s.size() - 1] == ']')) {
                s.erase(begin(s));
                s.erase(end(s) - 1);
                curr = &document.AddSection(s);
            } else {
                size_t it = s.find('=');
                (*curr)[s.substr(0, it)] = s.substr(it + 1, s.npos);
            }
        }
        return document;
    }
}
