#pragma once

#include <functional>
#include <algorithm>

template <class T>
class AVL {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;
        int height;

        Node(T v) : left(nullptr), right(nullptr), value(v), height(1) {}
    };

    AVL() : root(nullptr), node_count(0) {}

    ~AVL() {
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
        inorder_traversal(root, visit);
    }

    void preorder_traversal(std::function<void(T)> visit) const {
        preorder_traversal(root, visit);
    }

    void postorder_traversal(std::function<void(T)> visit) const {
        postorder_traversal(root, visit);
    }

private:
    Node* root;
    int node_count;

    int height(Node* n) const {
        return n ? n->height : 0;
    }

    int balance_factor(Node* n) const {
        return height(n->right) - height(n->left);
    }

    void update_height(Node* n) {
        if (n) {
            n->height = 1 + std::max(height(n->left), height(n->right));
        }
    }

    void clear(Node*& n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
        n = nullptr;
    }

    bool contains(Node* n, T item) const {
        if (!n) return false;
        if (item < n->value) return contains(n->left, item);
        if (item > n->value) return contains(n->right, item);
        return true;
    }

    Node* rotate_left(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        update_height(x);
        update_height(y);
        return y;
    }

    Node* rotate_right(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        update_height(y);
        update_height(x);
        return x;
    }

    void rebalance(Node*& n) {
        update_height(n);
        int bf = balance_factor(n);

        if (bf < -1) {
            if (balance_factor(n->left) > 0)
                n->left = rotate_left(n->left);  // LR case
            n = rotate_right(n);  // LL case
        } else if (bf > 1) {
            if (balance_factor(n->right) < 0)
                n->right = rotate_right(n->right);  // RL case
            n = rotate_left(n);  // RR case
        }
    }

    bool insert(Node*& n, T item) {
        if (!n) {
            n = new Node(item);
            ++node_count;
            return true;
        }

        if (item < n->value) {
            if (!insert(n->left, item)) return false;
        } else if (item > n->value) {
            if (!insert(n->right, item)) return false;
        } else {
            return false;  // duplicate
        }

        rebalance(n);
        return true;
    }

    Node* find_max(Node* n) {
        while (n->right) n = n->right;
        return n;
    }

    bool remove(Node*& n, T item) {
        if (!n) return false;

        if (item < n->value) {
            if (!remove(n->left, item)) return false;
        } else if (item > n->value) {
            if (!remove(n->right, item)) return false;
        } else {
            // Node found
            if (!n->left && !n->right) {
                delete n;
                n = nullptr;
            } else if (n->left && !n->right) {
                Node* temp = n;
                n = n->left;
                delete temp;
            } else if (!n->left && n->right) {
                Node* temp = n;
                n = n->right;
                delete temp;
            } else {
                Node* pred = find_max(n->left);
                n->value = pred->value;
                remove(n->left, pred->value);
            }
            --node_count;
        }

        if (n) rebalance(n);
        return true;
    }

    void inorder_traversal(Node* n, std::function<void(T)> visit) const {
        if (!n) return;
        inorder_traversal(n->left, visit);
        visit(n->value);
        inorder_traversal(n->right, visit);
    }

    void preorder_traversal(Node* n, std::function<void(T)> visit) const {
        if (!n) return;
        visit(n->value);
        preorder_traversal(n->left, visit);
        preorder_traversal(n->right, visit);
    }

    void postorder_traversal(Node* n, std::function<void(T)> visit) const {
        if (!n) return;
        postorder_traversal(n->left, visit);
        postorder_traversal(n->right, visit);
        visit(n->value);
    }
};