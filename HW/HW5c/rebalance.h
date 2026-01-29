#pragma once

#include <algorithm>

struct Node {
    Node* left;
    Node* right;
    int value;
    int height;

    Node(int v) : left(nullptr), right(nullptr), value(v), height(1) {}
};

// Helper to get height safely
int get_height(Node* node) {
    return node ? node->height : 0;
}

// Helper to update height from children
void update_height(Node* node) {
    if (node) {
        node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    }
}

// Right rotation (promote left child)
void promote_left(Node*& root) {
    Node* new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;

    update_height(root);
    update_height(new_root);

    root = new_root;
}

// Left rotation (promote right child)
void promote_right(Node*& root) {
    Node* new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;

    update_height(root);
    update_height(new_root);

    root = new_root;
}

// Rebalance AVL subtree rooted at root
void rebalance(Node*& root) {
    if (!root) return;

    update_height(root);

    int balance = get_height(root->right) - get_height(root->left);

    // Right-heavy
    if (balance > 1) {
        if (get_height(root->right->left) > get_height(root->right->right)) {
            promote_left(root->right); // Right-Left case
        }
        promote_right(root); // Right-Right case

        // Left-heavy
    } else if (balance < -1) {
        if (get_height(root->left->right) > get_height(root->left->left)) {
            promote_right(root->left); // Left-Right case
        }
        promote_left(root); // Left-Left case
    }
}
