#pragma once

#include <vector>

template <typename T>
void merge(std::vector<T>& items, std::vector<T>& left, std::vector<T>& right)
{
    size_t i = 0, j = 0, k = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            items[k++] = left[i++];
        } else {
            items[k++] = right[j++];
        }
    }

    while (i < left.size()) {
        items[k++] = left[i++];
    }

    while (j < right.size()) {
        items[k++] = right[j++];
    }
}

template <typename T>
void sort(std::vector<T>& items)
{
    if (items.size() <= 1) return;

    size_t mid = items.size() / 2;
    std::vector<T> left(items.begin(), items.begin() + mid);
    std::vector<T> right(items.begin() + mid, items.end());

    sort(left);
    sort(right);
    merge(items, left, right);
}
