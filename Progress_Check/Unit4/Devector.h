#pragma once
#include <cstddef>
#include <stdexcept>
#include <algorithm>  // for std::copy
#include "debug.h"

template <class T>
class Devector {
private:
    T* buffer = nullptr;
    size_t cap = 0;
    size_t sz = 0;
    size_t front_idx = 0;

    void ensure_capacity() {
        if (sz < cap)
            return;

        size_t new_cap = cap == 0 ? 8 : cap * 2;
        T* new_buf = new T[new_cap];

        for (size_t i = 0; i < sz; ++i) {
            new_buf[i] = std::move((*this)[i]);
        }

        delete[] buffer;
        buffer = new_buf;
        cap = new_cap;
        front_idx = 0;
    }

    size_t physical_index(size_t logical_index) const {
        return (front_idx + logical_index) % cap;
    }

public:
    Devector() = default;

    ~Devector() {
        delete[] buffer;
    }

    void push_back(const T& item) {
        ensure_capacity();
        buffer[physical_index(sz)] = item;
        ++sz;
    }

    void pop_back() {
        if (sz == 0) throw std::out_of_range("pop_back on empty Devector");
        --sz;
    }

    void push_front(const T& item) {
        ensure_capacity();
        front_idx = (front_idx + cap - 1) % cap;
        buffer[front_idx] = item;
        ++sz;
    }

    void pop_front() {
        if (sz == 0) throw std::out_of_range("pop_front on empty Devector");
        front_idx = (front_idx + 1) % cap;
        --sz;
    }

    T& operator[](size_t index) {
        return buffer[physical_index(index)];
    }

    const T& operator[](size_t index) const {
        return buffer[physical_index(index)];
    }

    T& at(size_t index) {
        if (index >= sz)
            throw std::out_of_range("at() index out of bounds");
        return (*this)[index];
    }

    size_t size() const {
        return sz;
    }

    void clear() {
        sz = 0;
        front_idx = 0;
    }
};
