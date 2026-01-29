# Unit 5 Progress Check

Write a Binary Search Tree with the following methods:

- `bool insert(T value)`
- `bool remove(T value)`
- `bool contains(T value)`
- `size_t size() const`
- `void clear()`
- `void inorder_traversal(std::function<void(T)> visit) const`
- `void preorder_traversal(std::function<void(T)> visit) const`
- `void postorder_traversal(std::function<void(T)> visit) const`

## Notes

Your traversal methods take a function named `visit` as a parameter. 
This function should be called with the value of each node in the tree. 

So, instead of printing the value, you should call `visit(node->value)`.

For the preorder and postorder traversals, process `left` before `right`.

Most of the tests depend on the *inorder* and *preorder* traversal methods. 
It is worth double checking that these are correct.

The file `scratch.cpp` is provided as a start for you to write your own BST tests.
It demonstrates how you can use the *traversal* methods to print your tree to `cout`. 

### C++ Lambda Syntax

The C++ syntax for passing functions as arguments to other functions is a little dense (surprise!).
While you don't actually need to write your own C++ lambdas (just make sure you call `visit` on your node values),
here's a brief explanation of what the syntax means:

```c++
#include <iostream>
int main() {
    BST<int> tree;
    tree.inorder_traversal([](int value) { std::cout << value << " "; });
    return 0;
}
```

The `[]` part begins a lambda function, which is a way to define an anonymous function in C++ 
The `(int value)` part is the parameter list—i.e. this function takes an `int` called `value`.
The `{ std::cout << value << " "; }` part is the function body—i.e. this function prints the value to `cout`.

In python, this would be written as:

```python
tree.inorder_traversal(lambda value: print(value, end=' '))
```

## Grading

| Test                                    | Points  |
|-----------------------------------------|---------|
| constructor_destructor_const_size_empty | 5       |
| size_after_insert                       | 5       |
| insert_balanced_inorder                 | 5       |
| insert_balanced_preorder                | 5       |
| insert_balanced_postorder               | 5       |
| contains                                | 5       |
| remove_leaves                           | 5       |
| remove_single_child                     | 5       |
| remove_two_children_simple              | 5       |
| remove_two_children_hard                | 5       |
| remove_root_until_empty                 | 5       |
| clear                                   | 5       |
| insert_duplicates                       | 5       |
| remove_missing                          | 5       |
| gamut                                   | 10      |
| no memory leaks                         | 5       |
| performance                             | 15      |
| **Total**                               | **100** |



