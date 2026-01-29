#pragma once

#include <vector>

template <class T>
void sort(std::vector<T> &array)
{
    for (size_t i = 1; i < array.size(); ++i) {
        T key = array[i];
        size_t j = i;
        while (j > 0 && key < array[j - 1]) {
            array[j] = array[j - 1];
            --j;
        }
        array[j] = key;
    }
}
