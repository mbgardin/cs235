#include <cstring>
#include <iostream>
#include <string>
#include "test_utils.h"
#include <set>
using std::set;
using std::cout;

#include "VectorSet.h"

// Checks that insert and contains work
TEST(insert_contains, 15) {
    std::cout << "--- Test 1 output ---\n" << std::endl;

    VectorSet<int> set;

    NOISY(set, insert, 10);
    NOISY(set, insert,4);
    NOISY(set, insert,5);
    NOISY(set, insert,2);
    NOISY(set, insert,10);

    std::cout << std::endl;

    ASSERT_EQ(set.contains(1), false)
    ASSERT_EQ(set.contains(2), true)
    ASSERT_EQ(set.contains(3), false)
    ASSERT_EQ(set.contains(4), true)
    ASSERT_EQ(set.contains(5), true)
    ASSERT_EQ(set.contains(6), false)
    ASSERT_EQ(set.contains(7), false)
    ASSERT_EQ(set.contains(8), false)
    ASSERT_EQ(set.contains(9), false)
    ASSERT_EQ(set.contains(10), true)

}

// Checks that remove works
TEST(remove, 15) {
    std::cout << "--- Test 2 output ---\n" << std::endl;

    VectorSet<std::string> set;

    set.insert("candle");
    set.insert("chair");
    set.insert("circle");
    set.insert("donkey");
    set.insert("dragon");
    set.insert("guitar");
    set.insert("spring");

    std::cout << "set = {candle, chair, circle, donkey, dragon, guitar, spring}" << std::endl;
    std::cout << std::endl;

    ASSERT_EQ(set.remove("spring"), true)
    ASSERT_EQ(set.remove("donkey"), true)
    ASSERT_EQ(set.remove("chair"), true)
    ASSERT_EQ(set.remove("coffee"), false)
    ASSERT_EQ(set.remove("guitar"), true)
    ASSERT_EQ(set.remove("chair"), false)
    ASSERT_EQ(set.remove("candle"), true)
    ASSERT_EQ(set.remove("circle"), true)
    ASSERT_EQ(set.remove("dragon"), true)
    ASSERT_EQ(set.remove("guitar"), false)
}

// Checks that empty and size work
TEST(empty_and_size, 15) {
    std::cout << "--- Test 3 output ---\n" << std::endl;

    VectorSet<std::string> set;

    ASSERT_EQ(set.empty(), true)


    NOISY(set, insert, "bottle");
    NOISY(set, insert, "flower");

    ASSERT_EQ(set.size(), 2)

    std::cout << std::endl;

    NOISY(set, insert, "bottle");
    ASSERT_EQ(set.size(), 2)

    std::cout << std::endl;

    NOISY(set, insert, "orange");
    ASSERT_EQ(set.size(), 3)

    std::cout << std::endl;

    NOISY(set, remove, "bottle");
    NOISY(set, remove, "butter");
    ASSERT_EQ(set.size(), 2)

    std::cout << std::endl;

    NOISY(set, insert, "bottle");
    ASSERT_EQ(set.size(), 3)

    std::cout << std::endl;

    NOISY(set, remove, "flower");
    NOISY(set, remove, "orange");
    NOISY(set, remove, "bottle");
    ASSERT_EQ(set.size(), 0)

    std::cout << std::endl;

    ASSERT_EQ(set.empty(), true)
}

// Checks that clear works
TEST(clear, 15) {
    std::cout << "--- Test 4 output ---\n" << std::endl;

    VectorSet<int> set;

    set.insert(4);
    set.insert(6);
    set.insert(7);
    set.insert(15);
    set.insert(16);
    set.insert(19);
    set.insert(23);
    set.insert(29);

    std::cout << "set = {4, 6, 7, 15, 16, 19, 23, 29}" << std::endl;
    ASSERT_EQ(set.size(), 8)
    ASSERT_EQ(set.empty(), false)

    std::cout << std::endl;

    NOISY(set, clear)

    std::cout << std::endl;

    ASSERT_EQ(set.size(), 0)
    ASSERT_EQ(set.empty(), true)

    std::cout << std::endl;

    NOISY(set, insert,4);

    ASSERT_EQ(set.size(), 1)
    ASSERT_EQ(set.empty(), false)
}


TEST(large_random, 20) {
	srand(235);

	set<int> stl_set;
	VectorSet<int> student_set;

	std::vector<int> result;
	std::vector<int> expected;

	// Add 1000 random numbers between 0 and 999
	for (int i = 0; i < 1000; i++) {
		int r = rand() % 1000;
		stl_set.insert(r);
		student_set.insert(r);
	}

	ASSERT_EQ(student_set.size(), stl_set.size());

	// Create vectors of whether the numbers between 0 and 999 were included
	for (int i = 0; i < 1000; i++) {
		result.push_back((stl_set.count(i) > 0));
		expected.push_back(student_set.contains(i));
	}

	ASSERT_VEQ(result, expected);
}


TEST(large_gamut, 20) {
	srand(25);

	set<int> stl_set;
	VectorSet<int> student_set;

	std::vector<int> result;
	std::vector<int> expected;

	// Add 1000 random numbers between 0 and 999
	for (int i = 0; i < 1000; i++) {
		int r = rand() % 1000;
		stl_set.insert(r);
		student_set.insert(r);
	}

	ASSERT_EQ(student_set.size(), stl_set.size());

	// Remove some of them
	for (int i = 0; i < 500; i++) {
		stl_set.erase(i);
		student_set.remove(i);
	}

	ASSERT_EQ(student_set.size(), stl_set.size());

	// Add some more
	for (int i = 0; i < 1000; i++) {
		int r = rand() % 1000 + 500;
		stl_set.insert(r);
		student_set.insert(r);
	}

	ASSERT_EQ(student_set.size(), stl_set.size());


	// Create vectors of whether the numbers between 0 and 1500 were included
	for (int i = 0; i < 1500; i++) {
		result.push_back((stl_set.count(i) > 0));
		expected.push_back(student_set.contains(i));
	}

	ASSERT_VEQ(result, expected);
}

TEST_MAIN()
