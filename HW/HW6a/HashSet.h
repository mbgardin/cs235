#pragma once

#include <vector>
#include <list>
#include <functional>
#include <algorithm>

template <typename T>
class HashSet {
public:
    HashSet() : buckets(initial_bucket_count), current_size(0) {}

    ~HashSet() = default;

    bool insert(const T& item) {
        if (contains(item)) return false;

        if (load_factor() > max_load_factor) {
            rehash(buckets.size() * 2);
        }

        size_t index = get_index(item);
        buckets[index].push_back(item);
        ++current_size;
        return true;
    }

    bool remove(const T& item) {
        size_t index = get_index(item);
        auto& chain = buckets[index];
        auto it = std::find(chain.begin(), chain.end(), item);
        if (it != chain.end()) {
            chain.erase(it);
            --current_size;
            return true;
        }
        return false;
    }

    bool contains(const T& item) const {
        size_t index = get_index(item);
        const auto& chain = buckets[index];
        return std::find(chain.begin(), chain.end(), item) != chain.end();
    }

    void clear() {
        for (auto& chain : buckets) {
            chain.clear();
        }
        current_size = 0;
    }

    int size() const {
        return static_cast<int>(current_size);
    }

private:
    static constexpr float max_load_factor = 0.75f;
    static constexpr size_t initial_bucket_count = 8;

    std::vector<std::list<T>> buckets;
    size_t current_size;

    float load_factor() const {
        return static_cast<float>(current_size) / static_cast<float>(buckets.size());
    }

    size_t get_index(const T& item) const {
        return std::hash<T>{}(item) % buckets.size();
    }

    void rehash(size_t new_bucket_count) {
        std::vector<std::list<T>> new_buckets(new_bucket_count);

        for (const auto& chain : buckets) {
            for (const auto& item : chain) {
                size_t new_index = std::hash<T>{}(item) % new_bucket_count;
                new_buckets[new_index].push_back(item);
            }
        }

        buckets = std::move(new_buckets);
    }
};