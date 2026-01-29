#pragma once
#include <functional>

template <class T>
class BST {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;

        Node(T v) : left(nullptr), right(nullptr), value(v) {}
    };

    BST() : root(nullptr), node_count(0) {}

    ~BST() {
        clear();
    }

    const Node* getRootNode() const {
        return root;
    }

    bool insert(T item) {
        return insert(root, item);
    }

    bool remove(T item) {
        return remove(root, item);
    }

    bool contains(T item) const {
        return contains(root, item);
    }

    void clear() {
        clear(root);
        root = nullptr;
        node_count = 0;
    }

    int size() const {
        return node_count;
    }

    void inorder_traversal(std::function<void(T)> visit) const {
        inorder(root, visit);
    }

    void preorder_traversal(std::function<void(T)> visit) const {
        preorder(root, visit);
    }

    void postorder_traversal(std::function<void(T)> visit) const {
        postorder(root, visit);
    }

private:
    Node* root;
    int node_count;

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    bool insert(Node*& node, T item) {
        if (!node) {
            node = new Node(item);
            ++node_count;
            return true;
        }
        if (item < node->value)
            return insert(node->left, item);
        if (item > node->value)
            return insert(node->right, item);
        return false;  // just a copy
    }

    bool contains(Node* node, T item) const {
        if (!node) return false;
        if (item < node->value)
            return contains(node->left, item);
        if (item > node->value)
            return contains(node->right, item);
        return true;
    }

    bool remove(Node*& node, T item) {
        if (!node) return false;
        if (item < node->value)
            return remove(node->left, item);
        else if (item > node->value)
            return remove(node->right, item);
        else {
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            } else if (node->left && !node->right) {
                Node* temp = node;
                node = node->left;
                delete temp;
            } else if (!node->left && node->right) {
                Node* temp = node;
                node = node->right;
                delete temp;
            } else {
                Node* pred = node->left;
                while (pred->right)
                    pred = pred->right;
                node->value = pred->value;
                // dont decrement, handled in my inner call
                remove(node->left, pred->value);
                return true;
            }
            --node_count;
            return true;
        }
    }

    void inorder(Node* node, std::function<void(T)> visit) const {
        if (!node) return;
        inorder(node->left, visit);
        visit(node->value);
        inorder(node->right, visit);
    }

    void preorder(Node* node, std::function<void(T)> visit) const {
        if (!node) return;
        visit(node->value);
        preorder(node->left, visit);
        preorder(node->right, visit);
    }

    void postorder(Node* node, std::function<void(T)> visit) const {
        if (!node) return;
        postorder(node->left, visit);
        postorder(node->right, visit);
        visit(node->value);
    }
};
