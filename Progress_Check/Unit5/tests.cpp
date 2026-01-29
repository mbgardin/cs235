#include "BST.h"
#include "test_utils.h"

template <typename T> void build_balanced_bst(BST<T> &tree) {
  std::vector<T> values = {10, 5, 15, 3, 8, 12, 18, 2, 4, 9, 11};
  for (const T &value : values) {
    tree.insert(value);
  }
}

template <typename T>
void check_preorder(BST<T> &tree, std::vector<T> const &preorder) {
  std::vector<T> result;
  tree.preorder_traversal([&](T value) { result.push_back(value); });
  ASSERT_EQ(result, preorder);
}

template <typename T>
void check_inorder(BST<T> &tree, std::vector<T> const &inorder)
{
  std::vector<T> result;
  tree.inorder_traversal([&](T value)
                         { result.push_back(value); });
  ASSERT_EQ(result, inorder);
}

std::vector<int> range(int start, int stop) {
  std::vector<int> range;
  for (int i = start; i < stop; i++) {
    range.push_back(i);
  }
  return range;
}

TEST(constructor_destructor_const_size_empty, 5) {
  const BST<int> tree;
  ASSERT_EQ(tree.size(), 0);
}

TEST(size_after_insert, 5) {
  BST<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  ASSERT_EQ(tree.size(), 3);
}

TEST(insert_balanced_inorder, 5) {
  BST<int> tree;
  build_balanced_bst(tree);
  std::vector<int> inorder = {2, 3, 4, 5, 8, 9, 10, 11, 12, 15, 18};
  std::vector<int> result;
  tree.inorder_traversal([&](int value) { result.push_back(value); });
  ASSERT_EQ(result, inorder);
}

TEST(insert_balanced_preorder, 5) {
  BST<int> tree;
  build_balanced_bst(tree);
  check_preorder(tree, {10, 5, 3, 2, 4, 8, 9, 15, 12, 11, 18});
}

TEST(insert_balanced_postorder, 5) {
  BST<int> tree;
  build_balanced_bst(tree);
  std::vector<int> postorder = {2, 4, 3, 9, 8, 5, 11, 12, 18, 15, 10};
  std::vector<int> result;
  tree.postorder_traversal([&](int value) { result.push_back(value); });
  ASSERT_EQ(result, postorder);
}

TEST(contains, 5) {
  BST<int> tree;
  build_balanced_bst(tree);
  ASSERT(tree.contains(10));
  ASSERT(tree.contains(15));
  ASSERT(tree.contains(18));

  ASSERT(!tree.contains(20));
  ASSERT(!tree.contains(1));
  ASSERT(!tree.contains(13));
  ASSERT(!tree.contains(7));
}

TEST(remove_leaves, 5) {
  BST<int> tree;
  build_balanced_bst(tree);

  tree.remove(2);
  tree.remove(4);
  tree.remove(9);
  tree.remove(11);

  std::vector<int> result;
  tree.inorder_traversal([&](int value) { result.push_back(value); });
  std::vector<int> inorder = {3, 5, 8, 10, 12, 15, 18};
  ASSERT_EQ(result, inorder);

  check_preorder(tree, {10, 5, 3, 8, 15, 12, 18});
}

TEST(remove_single_child, 5) {
  BST<int> tree;
  build_balanced_bst(tree);

  tree.remove(8);
  tree.remove(12);

  std::vector<int> result;
  tree.inorder_traversal([&](int value) { result.push_back(value); });
  std::vector<int> inorder = {2, 3, 4, 5, 9, 10, 11, 15, 18};
  ASSERT_EQ(result, inorder);

  check_preorder(tree, {10, 5, 3, 2, 4, 9, 15, 11, 18});
}

TEST(remove_two_children_simple, 5) {
  BST<int> tree;
  build_balanced_bst(tree);

  tree.remove(3);
  tree.remove(15);

  std::vector<int> result;
  tree.inorder_traversal([&](int value) { result.push_back(value); });
  std::vector<int> inorder = {2, 4, 5, 8, 9, 10, 11, 12, 18};
  ASSERT_EQ(result, inorder);

  check_preorder(tree, {10, 5, 2, 4, 8, 9, 12, 11, 18});
}

TEST(remove_two_children_hard, 5) {
  BST<int> tree;
  build_balanced_bst(tree);

  tree.remove(5);
  tree.remove(10);

  std::vector<int> result;
  tree.inorder_traversal([&](int value) { result.push_back(value); });
  std::vector<int> inorder = {2, 3, 4, 8, 9, 11, 12, 15, 18};
  ASSERT_EQ(result, inorder);

  check_preorder(tree, {9, 4, 3, 2, 8, 15, 12, 11, 18});
}

TEST(remove_root_until_empty, 5) {
  BST<int> tree;
  build_balanced_bst(tree);

  std::vector<int> to_remove = {10, 9, 8, 5, 4, 3, 2, 15, 12, 11, 18};

  tree.remove(10);
  check_preorder(tree, {9, 5, 3, 2, 4, 8, 15, 12, 11, 18});

  tree.remove(9);
  check_preorder(tree, {8, 5, 3, 2, 4, 15, 12, 11, 18});

  tree.remove(8);
  check_preorder(tree, {5, 3, 2, 4, 15, 12, 11, 18});

  tree.remove(5);
  check_preorder(tree, {4, 3, 2, 15, 12, 11, 18});

  tree.remove(4);
  check_preorder(tree, {3, 2, 15, 12, 11, 18});

  tree.remove(3);
  check_preorder(tree, {2, 15, 12, 11, 18});

  tree.remove(2);
  check_preorder(tree, {15, 12, 11, 18});

  tree.remove(15);
  check_preorder(tree, {12, 11, 18});

  tree.remove(12);
  check_preorder(tree, {11, 18});

  tree.remove(11);
  check_preorder(tree, {18});

  tree.remove(18);
  ASSERT_EQ(tree.size(), 0);
}

TEST(clear, 5) {
  BST<int> tree;
  build_balanced_bst(tree);
  ASSERT_EQ(tree.size(), 11);
  tree.clear();
  ASSERT_EQ(tree.size(), 0);
}

TEST(insert_duplicates, 5) {
  BST<int> tree;
  build_balanced_bst(tree);
  ASSERT(!tree.insert(2));
  ASSERT(!tree.insert(9));
  ASSERT(!tree.insert(10));
  ASSERT(!tree.insert(15));
  ASSERT(!tree.insert(18));
  ASSERT(tree.insert(20));
}

TEST(remove_missing, 5) {
  BST<int> tree;
  build_balanced_bst(tree);
  ASSERT(!tree.remove(20));
  ASSERT(!tree.remove(1));
  ASSERT(!tree.remove(13));
  ASSERT(!tree.remove(7));
  ASSERT(tree.remove(10));
}


void add_balanced(BST<int> &tree, int low, int high) {
  if (low > high)
    return;
  int mid = low + (high - low) / 2; // Compute middle index
  tree.insert(mid);
  add_balanced(tree, low, mid - 1);
  add_balanced(tree, mid + 1, high);
}

// Helper function to add N balanced items: values [0, N-1]
void add_balanced(BST<int> &tree, int N) { add_balanced(tree, 0, N - 1); }

TEST(gamut, 10) {
  BST<int> tree;
  add_balanced(tree, 100);

  tree.clear();
  ASSERT_EQ(tree.size(), 0);

  add_balanced(tree, 100);

  std::vector<int> inorder;
  tree.inorder_traversal([&](int value) { inorder.push_back(value); });
  check_inorder(tree, range(0, 100));

  for (int i : inorder) {
    tree.remove(i);
  }
  ASSERT_EQ(tree.size(), 0);

  tree.clear();
  ASSERT_EQ(tree.size(), 0);

  add_balanced(tree, 100);
  ASSERT_EQ(tree.size(), 100);


  for (int i = 0; i < 50; i++) {
    tree.remove(inorder[i]);
  }

  std::vector<int> expected_preorder = {74, 61, 55, 52, 50, 51, 53, 54, 58, 56, 57, 59, 60, 67, 64, 62, 63, 65, 66, 70, 68, 69, 72, 71, 73, 87, 80, 77, 75, 76, 78, 79, 83, 81, 82, 85, 84, 86, 93, 90, 88, 89, 91, 92, 96, 94, 95, 98, 97, 99};
  check_inorder(tree, range(50, 100));
  check_preorder(tree, expected_preorder);

  //try adding the items already in the tree again
  for (auto i : range(50, 100)) {
    tree.insert(i);
  }

  //Verify the tree stayed the same
  check_inorder(tree, range(50, 100));
  check_preorder(tree, expected_preorder);

  tree.clear();

  check_preorder(tree, {});
  check_inorder(tree, {});

}

TEST(performance, 15) {
  BST<int> tree;
  Timer timer;
  int N = 100;
  for (int round = 0; round < 5; round++) {
    add_balanced(tree, N);
  	ASSERT_EQ(tree.size(), N);
    for (int i = 0; i < tree.size(); i++) {
      tree.remove(i);
    }
    tree.clear();
    N *= 10;
    if (timer.seconds() > 60) {
      PARTIAL_CREDIT(round / 5.0);
    }
  }
}

DO_VALGRIND(5);

TEST_MAIN();