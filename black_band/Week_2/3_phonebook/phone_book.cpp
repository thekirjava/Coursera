#include "phone_book.h"

PhoneBook::PhoneBook(std::vector<Contact> contacts) {
    contacts_ = std::move(contacts);
    std::sort(begin(contacts_), end(contacts_),
              [](const Contact &lhs, const Contact &rhs) { return lhs.name < rhs.name; });
}

PhoneBook::ContactRange PhoneBook::FindByNamePrefix(std::string_view name_prefix) const {
    if (name_prefix.empty()) {
        return ContactRange(begin(contacts_), end(contacts_));
    }
    auto start = std::lower_bound(begin(contacts_), end(contacts_), name_prefix.data(),
                                  [](const Contact &lhs, const std::string &rhs) { return lhs.name < rhs; });
    if (start == end(contacts_)) {
        return ContactRange(end(contacts_), end(contacts_));
    }
    if (!IsPrefix(name_prefix, start->name)) {
        return ContactRange(end(contacts_), end(contacts_));
    }
    std::string next_prefix = NextString(name_prefix);
    auto last = std::lower_bound(begin(contacts_), end(contacts_), next_prefix,
                                 [](const Contact &lhs, const std::string &rhs) { return lhs.name < rhs; });
    return ContactRange(start, last);
}

std::string NextString(std::string_view str) {
    std::string ans = str.data();
    bool is_left = false;
    for (int i = ans.size() - 1; i >= 0; i--) {
        if (ans[i] != 'z') {
            ans[i]++;
            is_left = true;
            break;
        } else {
            ans[i] = 'a';
        }
    }
    if (!is_left) {
        ans = "a" + ans;
    }
    return ans;
}

bool IsPrefix(std::string_view prefix, std::string_view str) {
    if (prefix.size() > str.size()) {
        return false;
    }
    for (size_t i = 0; i < prefix.size(); i++) {
        if (prefix[i] != str[i]) {
            return false;
        }
    }
    return true;
}

PhoneBook DeserializePhoneBook(std::istream &input) {
    PhoneBookSerialize::ContactList list;
    list.ParseFromIstream(&input);
    std::vector<Contact> contacts;
    contacts.reserve(list.contact_size());
    for (const auto &protoContact: list.contact()) {
        Contact contact;
        contact.name = protoContact.name();
        if (protoContact.has_birthday()) {
            contact.birthday = {protoContact.birthday().year(), protoContact.birthday().month(),
                                protoContact.birthday().day()};
        }
        contact.phones.reserve(protoContact.phone_number_size());
        for (const auto &protoNumber: protoContact.phone_number()) {
            contact.phones.push_back(protoNumber);
        }
        contacts.push_back(contact);
    }
    return PhoneBook(contacts);
}

void PhoneBook::SaveTo(std::ostream &output) const {
    PhoneBookSerialize::ContactList list;
    for (const auto &contact:contacts_) {
        PhoneBookSerialize::Contact protoContact;
        protoContact.set_name(contact.name);
        if (contact.birthday.has_value()) {
            PhoneBookSerialize::Date protoDate;
            protoDate.set_day(contact.birthday->day);
            protoDate.set_month(contact.birthday->month);
            protoDate.set_year(contact.birthday->year);
            *protoContact.mutable_birthday() = protoDate;
        }
        if (!contact.phones.empty()) {
            for (const auto &number:contact.phones) {
                protoContact.add_phone_number(number);
            }
        }
        *list.add_contact() = protoContact;
    }
    list.SerializePartialToOstream(&output);
}
