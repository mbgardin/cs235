#include "test_utils.h"

#include "insertion_sort.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::cout, std::endl;

TEST(pre_sorted, 5)
{
    std::vector<int> items = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    sort(items);
    ASSERT_EQ(items, std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(reverse_sorted, 5)
{
    std::vector<int> items = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    sort(items);
    ASSERT_EQ(items, std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(spiral_sort, 5)
{
    std::vector<int> items = {1, 3, 5, 7, 9, 8, 6, 4, 2, 0};
    sort(items);
    ASSERT_EQ(items, std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(uniform_sort, 5)
{
    vector<int> items = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    vector<int> expected(items);
    sort(items);
    ASSERT_EQ(items, expected);
}

TEST(random_sort, 5)
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

TEST(sort_strings, 5)
{
    std::vector<string> items = {"a", "e", "b", "c", "d"};
    sort(items);
    ASSERT_EQ(items, std::vector<string>({"a", "b", "c", "d", "e"}));
}

long long calibrate(size_t N) 
{
    // Calibrate the timer
    int a = 0;
    int b = 1;
    Timer timer;
    timer.start();
    for (int i = 0; i < N; i++)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }
    timer.stop();
    return timer.nanoseconds();
}

TEST(performance, 15)
{
    /*
    Insertion sort be very quick on presorted data
    */

    const int N = 1000000;

    long long calibrated_ns = calibrate(N);
    cout << N << " swaps: " << calibrated_ns << endl;

    // Setup data
    vector<int> data(N);
    for (size_t i = 0; i < N; i++)
    {
        data[i] = i;
    }

    // Run insertion sort
    Timer sort_timer;
    sort_timer.start();
    sort(data);
    sort_timer.stop();

    cout << "Insertion Sort on " << N << " presorted items: " << sort_timer.nanoseconds() << endl;
    auto ratio = (sort_timer.nanoseconds() / calibrated_ns);
    cout << "Ratio: " << ratio << endl;
    ASSERT(ratio < 100, "Insertion Sort time must be < 100x the calibration time");
}

template <class T>
double fraction_sorted(T const& data) {
    size_t count = 0;
    for (size_t i = 1; i < data.size(); i++) {
        if (data[i] >= data[i-1]) { count++; }
    }
    return static_cast<double>(count) / (data.size() - 1);
}

TEST(partial_credit_sort, 50) {
    srand(235);
    const size_t N = 10000;
    vector<int> data(N);
    for (size_t i = 0; i < N; i++)
    {
        data[i] = rand();
    }

    double baseline_score = fraction_sorted(data);
    cout << "Already sorted pairs: " << baseline_score << endl;

    sort(data);
    
    double sorted_score = fraction_sorted(data);
    cout << "Sorted pairs after sort: " << sorted_score << endl;

    ASSERT(sorted_score > baseline_score, "Result should be more sorted than it was before calling sort.");

    double score = (sorted_score - baseline_score) / (1 - baseline_score);
    if (score < 1) { PARTIAL_CREDIT(score); }
}

struct C {
    int first;
    int second;
    
    C() {}
    
    C(C const& other) : first(other.first), second(other.second) {}
    
    C(int a, int b) : first(a), second(b) {}

    bool operator<(C const& b) const {
        return first < b.first;
    }
    bool operator>(C const& b) const {
        return first > b.first;
    }
    bool operator==(C const& b) const {
        return first == b.first;
    }
    bool operator <=(C const& b) const {
        return first <= b.first;
    }
    bool operator >=(C const& b) const {
        return first >= b.first;
    }
};

std::ostream& operator<<(std::ostream& out, C const& c) {
    return out << c.first << "(" << c.second << ")";
}

void fill_vector_c(vector<C> &items, size_t N) {
    size_t count_1(0), count_2(0), count_3(0);
    for (size_t i = 0; i < N; i++) {
        switch (rand() % 3 + 1) {
            case 1:
                items.push_back(C(1, count_1++));
            case 2:
                items.push_back(C(2, count_2++));
            case 3:
                items.push_back(C(3, count_3++));
        }
    }
}

bool check_stable(vector<C> const& items, vector<C> const& expected) {
    cout << "ASSERT: " << items << " == " << expected << endl;
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].first != expected[i].first || items[i].second != expected[i].second) {
            cout << "ERROR: " << items << " != " << expected << endl;
            return false;
        }
    }
    return true;
}

TEST(stable_sort, 5)
{
    /*
        Insertion sort should be stable.
    */

    vector<C> items = {C(5, 1), C(5, 2), C(2, 1), C(5, 3), C(2, 2), C(2, 3), C(5, 4)};
    vector<C> expected = {C(2, 1), C(2, 2), C(2, 3), C(5, 1), C(5, 2), C(5, 3), C(5, 4)};
    sort(items);
    ASSERT(check_stable(items, expected));

    vector<C> more_items = {C(3, 1), C(2, 1), C(4, 1), C(2, 2), C(2, 3), C(3, 2), C(4, 2)};
    vector<C> more_expected = {C(2, 1), C(2, 2), C(2, 3), C(3, 1), C(3, 2), C(4, 1), C(4, 2)};
    sort(more_items);
    ASSERT(check_stable(more_items, more_expected));
}

TEST_MAIN()
