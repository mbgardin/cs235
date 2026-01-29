#include "test_utils.h"

#include "merge.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::cout, std::endl;

TEST(pre_sorted, 15)
{
    std::vector<int> items = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    sort(items);
    ASSERT_EQ(items, std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(reverse_sort, 15)
{
    std::vector<int> items = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    sort(items);
    ASSERT_EQ(items, std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(spiral_sort, 15)
{
    std::vector<int> items = {1, 3, 5, 7, 9, 8, 6, 4, 2, 0};
    sort(items);
    ASSERT_EQ(items, std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(random_sort, 25)
{
    std::vector<int> items = {
        20, 94, 0, 34, 90, 82, 64, 54, 57, 81, 11,
        66, 41, 47, 76, 84, 88, 1, 5, 25, 13, 61,
        52, 91, 27, 31, 39, 14, 10, 12, 3, 43, 56,
        77, 6, 50, 18, 28, 83, 22, 73, 86, 67, 93,
        9, 21, 42, 49, 92, 7, 36, 17, 75, 40, 55,
        72, 19, 16, 59, 63, 70, 96, 45, 46, 51, 60,
        99, 85, 69, 95, 98, 23, 29, 79, 37, 65, 30,
        58, 97, 15, 35, 80, 8, 78, 89, 33, 68, 71,
        38, 74, 32, 53, 44, 24, 4, 48, 62, 2, 87, 26};

    std::vector<int> sorted_items = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
        40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
        50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
        60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
        70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
        90, 91, 92, 93, 94, 95, 96, 97, 98, 99};

    sort(items);
    ASSERT_EQ(items, sorted_items);
}

TEST(sort_strings, 10)
{
    std::vector<string> items = {"a", "e", "b", "c", "d"};
    sort(items);
    ASSERT_EQ(items, std::vector<string>({"a", "b", "c", "d", "e"}));
}

TEST(performance, 20)
{
    Timer timer;
    int N = 100;
    for (int round = 0; round < 5; round++) {
        long long calibrated_ns = calibrate(N);
        cout << N << " items" << endl;
        cout << "Calibration for " << N << " swaps: " << calibrated_ns << endl;

        // Setup data
        srand(7);
        vector<int> data(N);
        for (size_t i = 0; i < N; i++) {
            data[i] = rand();
        }
        // Run quicksort
        timer.start();
        sort(data);
        timer.stop();

        cout << "MergeSort on " << N << " items: " << timer.nanoseconds() << endl;
        auto ratio = (timer.nanoseconds() / calibrated_ns);
        cout << "Ratio: " << ratio << endl;
        ASSERT(ratio < 2000, "MergeSort time must be < 2000x the calibration time");
        cout << endl;

        if (timer.seconds() > 20) {
            FAIL;
        }

        N*=10;
    }
}

TEST_MAIN()
