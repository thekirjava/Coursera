#pragma once

#include <map>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void Serialize(T pod, std::ostream& out);

void Serialize(const std::string& str, std::ostream& out);

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out);

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);


// Deserialization

template <typename T>
void Deserialize(std::istream& in, T& pod);

void Deserialize(std::istream& in, std::string& str);

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data);

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);

// Serialization

template<typename T>
void Serialize(T pod, std::ostream &out) {
    out.write(reinterpret_cast<const char *>(&pod), sizeof(pod));
}

void Serialize(const std::string &str, std::ostream &out) {
    Serialize(str.size(), out);
    out.write(str.c_str(), str.size());
}

template<typename T>
void Serialize(const std::vector<T> &data, std::ostream &out) {
    Serialize(data.size(), out);
    for (const auto &value:data) {
        Serialize(value, out);
    }
}

template<typename T1, typename T2>
void Serialize(const std::map<T1, T2> &data, std::ostream &out) {
    Serialize(data.size(), out);
    for (const auto &[key, value]:data) {
        Serialize(key, out);
        Serialize(value, out);
    }
}


// Deserialization

template<typename T>
void Deserialize(std::istream &in, T &pod) {
    in.read(reinterpret_cast<char *>(&pod), sizeof(pod));
}

void Deserialize(std::istream &in, std::string &str) {
    size_t size = 0;
    Deserialize(in, size);
    str.resize(size);
    if (size > 0) {
        in.read(str.data(), str.size());
    }
}

template<typename T>
void Deserialize(std::istream &in, std::vector<T> &data) {
    size_t size = 0;
    Deserialize(in, size);
    data.resize(size);
    for (size_t i = 0; i < data.size(); i++) {
        Deserialize(in, data[i]);
    }
}

template<typename T1, typename T2>
void Deserialize(std::istream &in, std::map<T1, T2> &data) {
    size_t size = 0;
    Deserialize(in, size);
    for (size_t i = 0; i < size; i++) {
        T1 key;
        T2 value;
        Deserialize(in, key);
        Deserialize(in, value);
        data[key] = value;
    }
}