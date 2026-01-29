#include "pq.h"
#include "test_utils.h"

#include <queue>
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::cout, std::endl;
using std::vector;

TEST(constructor_size_empty, 5) {
    PQ<int> pq;
    ASSERT_EQ(pq.size(), 0);
}

TEST(empty, 5) {
    PQ<int> pq;
    ASSERT_EQ(pq.empty(), true);
    pq.push(1);
    ASSERT_EQ(pq.empty(), false);
    pq.pop();
    ASSERT_EQ(pq.empty(), true);
}

TEST(add_items_changes_size, 5) {
    PQ<int> pq;
    pq.push(1);
    pq.push(2);
    pq.push(3);
    ASSERT_EQ(pq.size(), 3);
}

TEST(remove_items_changes_size, 5) {
    PQ<int> pq;
    for (int i = 1; i < 6; i++) {
        NOISY(pq, push, i);
    }
    ASSERT_EQ(pq.size(), 5, "PQ size should be 5");

    for (int i = 4; i >= 0; --i) {
        NOISY(pq, pop);
        ASSERT_EQ(pq.size(), static_cast<size_t>(i), "PQ size should reduce when pop is called");
    }
}

TEST(top, 15) {
    PQ<string> names;
    names.push("Abinadi");
    names.push("Zeniff");
    names.push("Pahoran");
    names.push("Kishkuman");
    names.push("Nephi");
    names.push("Lehi");

    ASSERT_EQ(names.top(), "Zeniff");

    names.pop();
    ASSERT_EQ(names.top(), "Pahoran");

    names.pop();
    ASSERT_EQ(names.top(), "Nephi");
}

TEST(handles_duplicates, 15) {
    PQ<string> pq;
    vector<string> items = {"apple", "banana", "carrot", "apple", "banana", "carrot"};

    for (const auto& item : items) {
        NOISY(pq, push, item);
    }

    ASSERT_EQ(pq.top(), "carrot"); pq.pop();
    ASSERT_EQ(pq.top(), "carrot"); pq.pop();
    ASSERT_EQ(pq.top(), "banana"); pq.pop();
    ASSERT_EQ(pq.top(), "banana"); pq.pop();
    ASSERT_EQ(pq.top(), "apple"); pq.pop();
    ASSERT_EQ(pq.top(), "apple");
}

TEST(add_remove_add_items, 25) {
    PQ<int> pq;
    ASSERT_EQ(pq.size(), 0, "PQ size should be 0");

    for (int i = 1; i <= 50; i++) pq.push(i);

    for (int i = 50; i > 40; i--) {
        ASSERT_EQ(pq.top(), i);
        pq.pop();
    }

    for (int i = 100; i <= 150; i++) pq.push(i);

    for (int i = 150; i > 140; i--) {
        ASSERT_EQ(pq.top(), i);
        pq.pop();
    }

    for (int i = 1; i <= 50; i++) pq.push(i);

    for (int i = 140; i > 130; i--) {
        ASSERT_EQ(pq.top(), i);
        pq.pop();
    }
}

TEST(large_random, 25) {
    srand(235);

    PQ<int> student_pq;
    std::priority_queue<int> stl_pq;

    vector<int> result;
    vector<int> expected;

    for (int i = 0; i < 1000; i++) {
        int r = rand();
        student_pq.push(r);
        stl_pq.push(r);
    }

    for (int i = 0; i < 1000; i++) {
        result.push_back(student_pq.top());
        expected.push_back(stl_pq.top());
        student_pq.pop();
        stl_pq.pop();
    }

    ASSERT_VEQ(result, expected);
}

TEST_MAIN()
