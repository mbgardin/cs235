#pragma once
#include <functional>
#include <algorithm>
//this is so hard but god is good, even learning how to debug on the final haha
template <class T>
class AVL {
private:
    struct Node {
        T data;
        int height;
        Node* left;
        Node* right;

        Node(const T& d) : data(d), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int size_;

    int height(Node* n) const {
        return n ? n->height : 0;
    }

    int balance_factor(Node* n) const {
        return height(n->left) - height(n->right);
    }

    void update_height(Node* n) {
        n->height = 1 + std::max(height(n->left), height(n->right));
    }

    Node* rotate_right(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        update_height(y);
        update_height(x);
        return x;
    }

    Node* rotate_left(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        update_height(x);
        update_height(y);
        return y;
    }

    Node* rebalance(Node* node) {
        update_height(node);
        int balance = balance_factor(node);
        if (balance > 1) {
            if (balance_factor(node->left) < 0)
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        if (balance < -1) {
            if (balance_factor(node->right) > 0)
                node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        return node;
    }

    Node* insert(Node* node, const T& value, bool& inserted) {
        if (!node) {
            inserted = true;
            return new Node(value);
        }
        if (value < node->data)
            node->left = insert(node->left, value, inserted);
        else if (value > node->data)
            node->right = insert(node->right, value, inserted);
        return rebalance(node);
    }

    Node* remove(Node* node, const T& value, bool& removed) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = remove(node->left, value, removed);
        } else if (value > node->data) {
            node->right = remove(node->right, value, removed);
        } else {
            removed = true;

            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }

            Node* succParent = node;
            Node* succ = node->right;
            while (succ->left) {
                succParent = succ;
                succ = succ->left;
            }

            if (succParent != node) {
                succParent->left = succ->right;
                succ->right = node->right;
            }

            succ->left = node->left;
            delete node;
            node = succ;
        }

        update_height(node);
        return rebalance(node);
    }

    bool contains(Node* node, const T& value) const {
        if (!node) return false;
        if (value < node->data)
            return contains(node->left, value);
        else if (value > node->data)
            return contains(node->right, value);
        return true;
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void inorder(Node* node, std::function<void(T)> visit) const {
        if (!node) return;
        inorder(node->left, visit);
        visit(node->data);
        inorder(node->right, visit);
    }

    void preorder(Node* node, std::function<void(T)> visit) const {
        if (!node) return;
        visit(node->data);
        preorder(node->left, visit);
        preorder(node->right, visit);
    }

    void postorder(Node* node, std::function<void(T)> visit) const {
        if (!node) return;
        postorder(node->left, visit);
        postorder(node->right, visit);
        visit(node->data);
    }

public:
    AVL() : root(nullptr), size_(0) {}
    ~AVL() { clear(); }

    bool insert(T item) {
        bool inserted = false;
        root = insert(root, item, inserted);
        if (inserted) ++size_;
        return inserted;
    }

    bool remove(T item) {
        bool removed = false;
        root = remove(root, item, removed);
        if (removed) --size_;
        return removed;
    }

    bool contains(T item) const {
        return contains(root, item);
    }

    void clear() {
        clear(root);
        root = nullptr;
        size_ = 0;
    }

    int size() const {
        return size_;
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
};