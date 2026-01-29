#pragma once

#include <cstddef>       // for size_t
#include <stdexcept>     // for std::out_of_range
#include <algorithm>     // for std::copy, std::move

template<class T>
class Vector {
private:
    T* data = nullptr;
    size_t sz = 0;
    size_t cap = 0;

    void grow() {
        cap = (cap == 0) ? 1 : cap * 2;
        T* new_data = new T[cap];
        for (size_t i = 0; i < sz; ++i) {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
    }

public:
    Vector() = default;

    ~Vector() {
        delete[] data;
    }

    void push_back(T const& item) {
        if (sz == cap) grow();
        data[sz++] = item;
    }

    void pop_back() {
        if (sz == 0) throw std::out_of_range("pop_back on empty vector");
        --sz;
    }

    void insert(T const& item, size_t position) {
        if (position > sz) throw std::out_of_range("insert position out of range");
        if (sz == cap) grow();
        for (size_t i = sz; i > position; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[position] = item;
        ++sz;
    }

    void remove(size_t position) {
        if (position >= sz) throw std::out_of_range("remove position out of range");
        for (size_t i = position; i + 1 < sz; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --sz;
    }

    T& operator[](size_t index) {
        return data[index]; // unsafe version (like std::vector::operator[])
    }

    T& at(size_t index) {
        if (index >= sz) throw std::out_of_range("index out of range");
        return data[index];
    }

    size_t size() const {
        return sz;
    }

    void clear() {
        sz = 0;
    }
};
