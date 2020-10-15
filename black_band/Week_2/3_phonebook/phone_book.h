#pragma once

#include "iterator_range.h"

#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <iosfwd>
#include <algorithm>

#include "contact.pb.h"

struct Date {
    int year, month, day;
};

struct Contact {
    std::string name;
    std::optional<Date> birthday;
    std::vector<std::string> phones;
};

class PhoneBook {
public:
    using ContactRange = IteratorRange<std::vector<Contact>::const_iterator>;
    explicit PhoneBook(std::vector<Contact> contacts);

    ContactRange FindByNamePrefix(std::string_view name_prefix) const;

    void SaveTo(std::ostream& output) const;

private:

    std::vector<Contact> contacts_;
};

PhoneBook DeserializePhoneBook(std::istream& input);
std::string NextString(std::string_view str);
bool IsPrefix(std::string_view prefix, std::string_view str);