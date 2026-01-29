#pragma once
#include <cstdlib>
#include <functional>
#include <memory>

template <typename T>
class BST {
private:
    struct Node {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(const T& val) : value(val) {}
    };

    std::unique_ptr<Node> root;
    size_t node_count = 0;

    bool insert(std::unique_ptr<Node>& node, const T& value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            ++node_count;
            return true;
        }
        if (value < node->value)
            return insert(node->left, value);
        if (value > node->value)
            return insert(node->right, value);
        return false; // Duplicate
    }

    bool contains(const std::unique_ptr<Node>& node, const T& value) const {
        if (!node) return false;
        if (value < node->value) return contains(node->left, value);
        if (value > node->value) return contains(node->right, value);
        return true;
    }

    bool remove(std::unique_ptr<Node>& node, const T& value) {
        if (!node) return false;
        if (value < node->value) return remove(node->left, value);
        if (value > node->value) return remove(node->right, value);

        // Node found
        if (node->left && node->right) {
            // Find in-order successor (leftmost node in right subtree)
            std::unique_ptr<Node>* successor = &node->right;
            while ((*successor)->left) {
                successor = &(*successor)->left;
            }
            node->value = (*successor)->value; // Copy successor's value
            return remove(*successor, node->value); // Remove successor
        }

        // Node has one or zero children
        node = std::move(node->left ? node->left : node->right);
        --node_count;
        return true;
    }

    void inorder(const std::unique_ptr<Node>& node, const std::function<void(T)>& visit) const {
        if (!node) return;
        inorder(node->left, visit);
        visit(node->value);
        inorder(node->right, visit);
    }

    void preorder(const std::unique_ptr<Node>& node, const std::function<void(T)>& visit) const {
        if (!node) return;
        visit(node->value);
        preorder(node->left, visit);
        preorder(node->right, visit);
    }

    void postorder(const std::unique_ptr<Node>& node, const std::function<void(T)>& visit) const {
        if (!node) return;
        postorder(node->left, visit);
        postorder(node->right, visit);
        visit(node->value);
    }

public:
    BST() = default;
    ~BST() = default;

    bool insert(const T& value) {
        return insert(root, value);
    }

    bool contains(const T& value) const {
        return contains(root, value);
    }

    bool remove(const T& value) {
        return remove(root, value);
    }

    void inorder_traversal(std::function<void(T)> visit) const {
        inorder(root, std::move(visit));
    }

    void preorder_traversal(std::function<void(T)> visit) const {
        preorder(root, std::move(visit));
    }

    void postorder_traversal(std::function<void(T)> visit) const {
        postorder(root, std::move(visit));
    }

    size_t size() const {
        return node_count;
    }

    void clear() {
        root.reset();
        node_count = 0;
    }
};
