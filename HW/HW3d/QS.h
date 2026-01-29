#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <iterator>

constexpr int INSERTION_SORT_THRESHOLD = 16;

template <typename T>
void insertion_sort(std::vector<T>& arr, int left, int right)
{
    for (int i = left + 1; i <= right; ++i)
    {
        T key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void quicksort(std::vector<T>& arr, int low, int high, std::mt19937& gen)
{
    while (low < high)
    {
        if (high - low + 1 <= INSERTION_SORT_THRESHOLD)
        {
            insertion_sort(arr, low, high);
            return;
        }

        std::uniform_int_distribution<> dis(low, high);
        std::swap(arr[dis(gen)], arr[high]);
        const T& pivot = arr[high];

        int lt = low, i = low, gt = high;

        while (i <= gt)
        {
            if (arr[i] < pivot)
            {
                std::swap(arr[lt++], arr[i++]);
            }
            else if (arr[i] > pivot)
            {
                std::swap(arr[i], arr[gt--]);
            }
            else
            {
                ++i;
            }
        }

        if (lt - low < high - gt)
        {
            quicksort(arr, low, lt - 1, gen);
            low = gt + 1;
        }
        else
        {
            quicksort(arr, gt + 1, high, gen);
            high = lt - 1;
        }
    }
}

template <typename T>
void sort(std::vector<T>& arr)
{
    if (arr.empty()) return;
    std::random_device rd;
    std::mt19937 gen(rd());
    quicksort(arr, 0, static_cast<int>(arr.size() - 1), gen);
}
