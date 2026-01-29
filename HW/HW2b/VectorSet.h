#pragma once
#include <cstdlib>
#include <vector>
#include <algorithm>

template<class T>
class VectorSet {
private:
    std::vector<T> _vec;

public:
    bool contains(T item) const {
        for (const T& val : _vec) {
            if (val == item) {
                return true;
            }
        }
        return false;
    }

    bool insert(T item) {
        if (!contains(item)) {
            _vec.push_back(item);
            return true;
        }
        return false;
    }

    bool remove(T item) {
        for (size_t i = 0; i < _vec.size(); ++i) {
            if (_vec[i] == item) {
                std::swap(_vec[i], _vec.back());
                _vec.pop_back();
                return true;
            }
        }
        return false;
    }

    size_t size() const {
        return _vec.size();
    }

    bool empty() const {
        return _vec.empty();
    }

    void clear() {
        _vec.clear();
    }
};
