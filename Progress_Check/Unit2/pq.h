#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>

template <class T>
class PQ {
private:
    std::vector<T> data;

    void heapify_up(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (data[index] > data[parent]) {
                std::swap(data[index], data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapify_down(size_t index) {
        size_t n = data.size();
        while (2 * index + 1 < n) {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t largest = index;

            if (left < n && data[left] > data[largest]) largest = left;
            if (right < n && data[right] > data[largest]) largest = right;

            if (largest == index) break;

            std::swap(data[index], data[largest]);
            index = largest;
        }
    }

public:
    void push(T const& item) {
        data.push_back(item);
        heapify_up(data.size() - 1);
    }

    void pop() {
        if (empty()) throw std::out_of_range("pop from empty PQ");
        std::swap(data[0], data.back());
        data.pop_back();
        if (!empty()) heapify_down(0);
    }

    size_t size() const {
        return data.size();
    }

    T top() const {
        if (empty()) throw std::out_of_range("top from empty PQ");
        return data[0];
    }

    bool empty() const {
        return data.empty();
    }
};
