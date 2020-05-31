#include "phone_number.h"
#include <stdexcept>

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
    this->local_number_ = "";
    this->city_code_ = "";
    this->country_code_ = "";
    int counter = 0;
    for (char c:international_number) {
        if (c == '-') {
            counter++;
        }
    }
    if ((international_number[0] != '+') || (counter < 2)) {
        throw invalid_argument("invalid_argument");
    }
    int i = 1;
    for (; international_number[i] != '-'; i++) {
        this->country_code_ += international_number[i];
    }
    i++;
    for (; international_number[i] != '-'; i++) {
        this->city_code_ += international_number[i];
    }
    i++;
    for (; i < international_number.size(); i++) {
        this->local_number_ += international_number[i];
    }
    if ((this->country_code_ == "") || (this->city_code_ == "") || (this->local_number_ == "")) {
        throw invalid_argument("invalid_argument");
    }
}

string PhoneNumber::GetCountryCode() const {
    return this->country_code_;
}

string PhoneNumber::GetCityCode() const {
    return this->city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return this->local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + this->country_code_ + "-" + this->city_code_ + "-" + this->local_number_;
}
