#include <cstring>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

#include "SLList.h"

#include "test_utils.h"

template<class T, class E>
void assert_lists(SLList<T> const &obs, E const &exp) {
    ASSERT_EQ(obs.size(), exp.size());
    const typename SLList<T>::Node *node = obs.get_head();

    for (size_t i = 0; i < exp.size(); i++) {
        if (node == nullptr) { FAIL; }
        if (node->value != exp[i]) {
            std::cout << "ERROR: mismatch at position " << i;
            std::cout << " " << node->value << " != " << exp[i] << std::endl;
            FAIL;
        }
        node = node->next;
    }
}

template<class T, class E>
void assert_linked_lists(SLList<T> const &obs, E const &exp) {
    ASSERT_EQ(obs.size(), exp.size());
    const typename SLList<T>::Node *node = obs.get_head();
    int counter = 0;
    for (auto it = exp.begin(); it != exp.end(); ++it) {
        if (node == nullptr) { FAIL; }
        if (node->value != *it) {
            std::cout << "ERROR: mismatch at position " << counter;
            std::cout << " " << node->value << " != " << *it << std::endl;
            FAIL;
        }
        node = node->next;
        counter++;
    }
}

TEST(constructor_destructor_const_size_empty, 5)
{
    SLList<float> list;
    ASSERT_EQ(list.size(), 0);
}

TEST(push_back_size, 5)
{
    SLList<float> list;
    ASSERT_EQ(list.size(), 0);
    list.push_back(1);
    ASSERT_EQ(list.size(), 1);
    list.push_back(2);
    ASSERT_EQ(list.size(), 2);
    list.push_back(3);
    ASSERT_EQ(list.size(), 3);
}

TEST(push_pop_back_size, 5)
{
    SLList<int> list;
    ASSERT_EQ(list.size(), 0);
    for (size_t i = 0; i < 100; i++) {
        list.push_back(i);
    }
    ASSERT_EQ(list.size(), 100);

    for (size_t i = 0; i < 100; i++) {
        list.pop_back();
    }
    ASSERT_EQ(list.size(), 0);
}

TEST(push_back_contents, 5) {
    SLList<int> list;
    for (size_t i = 0; i < 10; i++) {
        list.push_back(i);
    }
    std::vector<int> exp = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert_lists(list, exp);
}

TEST(push_back_strings, 5) {
    SLList<std::string> list;
    list.push_back("butterfly");
    list.push_back("can");
    list.push_back("flower");
    list.push_back("library");

    std::vector<std::string> exp = {"butterfly", "can", "flower", "library"};
    assert_lists(list, exp);
}

TEST(push_pop_front_size, 5)
{
    SLList<float> list;
    ASSERT_EQ(list.size(), 0);
    list.push_front(1);
    ASSERT_EQ(list.size(), 1);
    list.push_front(2);
    ASSERT_EQ(list.size(), 2);
    list.push_front(3);
    ASSERT_EQ(list.size(), 3);
    list.pop_front();
    ASSERT_EQ(list.size(), 2);
    list.pop_front();
    ASSERT_EQ(list.size(), 1);
    list.pop_front();
    ASSERT_EQ(list.size(), 0);
}

TEST(push_front_contents, 5) {
    SLList<int> list;
    for (size_t i = 0; i < 10; i++) {
        list.push_front(i);
    }
    std::vector<int> exp = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    assert_lists(list, exp);
}


TEST(push_front_back_contents, 5) {
    SLList<int> list;
    for (size_t i = 0; i < 10; i++) {
        if (i & 1) {
            list.push_back(i);
        } else {
            list.push_front(i);
        }
    }
    std::vector<int> exp = {8, 6, 4, 2, 0, 1, 3, 5, 7, 9};
    assert_lists(list, exp);
}

TEST(push_pop_front_contents, 5) {
    SLList<int> list;
    for (size_t i = 0; i < 10; i++) {
        list.push_front(i);
    }

    for (size_t i = 0; i < 5; i++) {
        list.pop_front();
    }
    std::vector<int> exp = {4,3,2,1,0};
    assert_lists(list, exp);
}

TEST(front, 5)
{
    SLList<int> list;

    for (size_t i = 0; i < 5; i++) {
        list.push_back(i);
        ASSERT_EQ(list.front(), 0);
    }

    list.clear();

    list.push_back(13);

    ASSERT_EQ(list.front(), 13);

    list.pop_back();
    ASSERT_EQ(list.size(), 0);
}

TEST(clear, 10)
{
    SLList<int> list;

    for (size_t i = 0; i < 5; i++) {
        list.push_back(i);
    }

    ASSERT_EQ(list.size(), 5);

    list.clear();
    ASSERT_EQ(list.size(), 0);

    auto head = list.get_head();
    ASSERT_EQ(head, nullptr);

    for (size_t i = 0; i < 5; i++) {
        list.push_back(i);
    }

    ASSERT_EQ(list.size(), 5);
}


TEST(gamut, 20)
{
    SLList<int> list;
    std::list<int> exp;

    for (size_t i = 0; i < 1000; i++) {
        list.push_front(i);
        exp.push_front(i);
    }
    assert_linked_lists(list, exp);

    for (size_t i = 0; i < 1000; i++) {
        list.push_back(i);
        exp.push_back(i);
    }
    assert_linked_lists(list, exp);

    for (size_t i = 0; i < 500; i++) {
        list.pop_front();
        exp.pop_front();
    }
    assert_linked_lists(list, exp);

    for (size_t i = 0; i < 250; i++) {
        list.pop_back();
        exp.pop_back();
    }
    assert_linked_lists(list, exp);
    ASSERT_EQ(list.size(), exp.size());

    while (list.size() > 0) {
        list.pop_front();
        exp.pop_front();
    }

    list.clear();
    exp.clear();
    assert_linked_lists(list, exp);

    for (size_t i = 0; i < 1000; i++) {
        list.push_back(i);
    }

    list.clear();

    auto head = list.get_head();
    ASSERT_EQ(head, nullptr);
}


TEST(performance, 10)
{
    Timer timer;
    int N = 100;
    for (int round = 0; round < 4; round++) {
        long long calibrated_ns = calibrate(N);
        std::cout << N << " items" << std::endl;
        std::cout << "Calibration for " << N << " swaps: " << calibrated_ns << std::endl;

        timer.start();

        SLList<int> list;
        for (size_t i = 0; i < N; i++) {
            list.push_front(i);
        }
        timer.stop();

        std::cout << "SLL push_front on " << N << " items: " << timer.nanoseconds() << std::endl;
        auto ratio = (timer.nanoseconds() / calibrated_ns);
        std::cout << "Ratio: " << ratio << std::endl;
        ASSERT(ratio < 200, "SLL push_front time must be < 200x the calibration time");
        std::cout << std::endl;

        if (timer.seconds() > 20) {
            FAIL;
        }

        N*=10;
    }
}

DO_VALGRIND(10);

TEST_MAIN();
