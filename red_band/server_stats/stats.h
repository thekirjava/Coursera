#pragma once

#include "http_request.h"

#include <string_view>
#include <map>

using namespace std;

const string GET = "GET";
const string PUT = "PUT";
const string POST = "POST";
const string DELETE = "DELETE";
const string SLASH = "/";
const string ORDER = "/order";
const string PRODUCT = "/product";
const string BASKET = "/basket";
const string HELP = "/help";
const string UNKNOWN_METHOD = "UNKNOWN";
const string UNKNOWN_URI = "unknown";

class Stats {
public:
    Stats() {
        m[GET] = 0;
        m[PUT] = 0;
        m[POST] = 0;
        m[DELETE] = 0;
        m[UNKNOWN_METHOD] = 0;
        u[SLASH] = 0;
        u[ORDER] = 0;
        u[PRODUCT] = 0;
        u[BASKET] = 0;
        u[HELP] = 0;
        u[UNKNOWN_URI] = 0;
    }

    void AddMethod(string_view method);

    void AddUri(string_view uri);

    const map<string_view, int> &GetMethodStats() const;

    const map<string_view, int> &GetUriStats() const;

private:

    map<string_view, int> m;
    map<string_view, int> u;
};

HttpRequest ParseRequest(string_view line);
