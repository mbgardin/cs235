#pragma once

#include <iostream>   // for stream output
#include <string>     // for std::string
#include <cstddef>    // for size_t
#include <stdexcept>  // for std::out_of_range
#include <algorithm>  // for std::move

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

    void push_back(const T& item) {
        if (sz == cap) grow();
        data[sz++] = item;
    }

    void pop_back() {
        if (sz == 0) throw std::out_of_range("pop_back on empty vector");
        --sz;
    }

    void insert(const T& item, size_t position) {
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
        return data[index]; // unchecked access
    }

    T& at(size_t index) {
        if (index >= sz) throw std::out_of_range("at: index out of range");
        return data[index];
    }

    size_t size() const {
        return sz;
    }

    void clear() {
        sz = 0;
    }

    class Iterator {
    private:
        T* currItem;
    public:
        Iterator(T* ptr) : currItem(ptr) {}

        T& operator*() {
            return *currItem;
        }

        Iterator& operator++() {
            ++currItem;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return currItem == other.currItem;
        }

        bool operator!=(const Iterator& other) const {
            return currItem != other.currItem;
        }
    };

    using iterator = Iterator;

    iterator begin() {
        return iterator(data);
    }

    iterator end() {
        return iterator(data + sz);
    }
};
