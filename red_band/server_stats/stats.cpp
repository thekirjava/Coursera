#include "stats.h"

void Stats::AddMethod(string_view method) {
    if (method == "GET") {
        m[GET]++;
    } else if (method == "PUT") {
        m[PUT]++;
    } else if (method == "POST") {
        m[POST]++;
    } else if (method == "DELETE") {
        m[DELETE]++;
    } else {
        m[UNKNOWN_METHOD]++;
    }
}

void Stats::AddUri(string_view uri) {
    if (uri == "/") {
        u[SLASH]++;
    } else if (uri == "/order") {
        u[ORDER]++;
    } else if (uri == "/product") {
        u[PRODUCT]++;
    } else if (uri == "/basket") {
        u[BASKET]++;
    } else if (uri == "/help") {
        u[HELP]++;
    } else {
        u[UNKNOWN_URI]++;
    }
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return m;
}

const map<string_view, int> &Stats::GetUriStats() const {
    return u;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest request;
    while (line.find(" ", 0) == 0) {
        line.remove_prefix(1);
    }
    int pos = line.find(" ", 0);
    request.method = *(new string(line.substr(0, pos)));
    line.remove_prefix(pos + 1);
    pos = line.find(" ", 0);
    request.uri = *(new string(line.substr(0, pos)));
    line.remove_prefix(pos + 1);
    request.protocol = *(new string(line.substr(0, line.npos)));
    return request;
}
