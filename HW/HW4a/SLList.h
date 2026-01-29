#pragma once

template <class T>
class SLList {
public:
    struct Node {
        Node* next;
        T value;

        Node(T v) : next(nullptr), value(v) {}
    };

    SLList() : head(nullptr), list_size(0) {}

    ~SLList() {
        clear();
    }

    const Node* get_head() const {
        return head;
    }

    void push_back(T item) {
        Node* new_node = new Node(item);
        if (!head) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
        ++list_size;
    }

    void pop_back() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* current = head;
            while (current->next && current->next->next) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        --list_size;
    }

    void push_front(T item) {
        Node* new_node = new Node(item);
        new_node->next = head;
        head = new_node;
        ++list_size;
    }

    void pop_front() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        --list_size;
    }

    const T& front() const {
        return head->value;
    }

    int size() const {
        return list_size;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        list_size = 0;
    }

private:
    Node* head;
    int list_size;
};
