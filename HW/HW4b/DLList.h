#pragma once
#include <stdexcept>

template<class T>
class DLList {
public:
    struct Node {
        Node* prev;
        Node* next;
        T value;
        Node(T v) : prev(nullptr), next(nullptr), value(v) {}
    };

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;

    Node* get_node_at(int index) const {
        if (index < 0 || index >= count) throw std::out_of_range("Index out of range");
        Node* node = head;
        for (int i = 0; i < index; ++i) {
            node = node->next;
        }
        return node;
    }

public:
    DLList() = default;

    ~DLList() {
        clear();
    }

    const Node* get_head() const {
        return head;
    }

    void push_front(T item) {
        Node* node = new Node(item);
        node->next = head;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = head;
        ++count;
    }

    void push_back(T item) {
        Node* node = new Node(item);
        node->prev = tail;
        if (tail) tail->next = node;
        tail = node;
        if (!head) head = tail;
        ++count;
    }

    void insert(T item, int position) {
        if (position < 0 || position > count) throw std::out_of_range("Insert position out of range");
        if (position == 0) return push_front(item);
        if (position == count) return push_back(item);

        Node* next_node = get_node_at(position);
        Node* prev_node = next_node->prev;

        Node* new_node = new Node(item);
        new_node->prev = prev_node;
        new_node->next = next_node;

        prev_node->next = new_node;
        next_node->prev = new_node;
        ++count;
    }

    void pop_front() {
        if (!head) throw std::out_of_range("List is empty");
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        --count;
    }

    void pop_back() {
        if (!tail) throw std::out_of_range("List is empty");
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        --count;
    }

    void remove(int position) {
        if (position < 0 || position >= count) throw std::out_of_range("Remove position out of range");
        if (position == 0) return pop_front();
        if (position == count - 1) return pop_back();

        Node* node = get_node_at(position);
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        --count;
    }

    const T& front() const {
        if (!head) throw std::out_of_range("List is empty");
        return head->value;
    }

    const T& back() const {
        if (!tail) throw std::out_of_range("List is empty");
        return tail->value;
    }

    const T& at(int index) const {
        return get_node_at(index)->value;
    }

    bool contains(const T& item) const {
        for (Node* node = head; node != nullptr; node = node->next) {
            if (node->value == item) return true;
        }
        return false;
    }

    int size() const {
        return count;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        count = 0;
    }
};
