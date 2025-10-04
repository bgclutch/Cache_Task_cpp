#pragma once

#include <climits>
#include <unordered_map>
#include <map>
#include <queue>
#include <vector>
#include <cassert>
#include <cstddef>

namespace belady {

template <typename KeyType>
class belady_cache_t {
 private:
    size_t cache_size_ = 0;

    using Index = size_t;
    using Position = size_t;
    using IndexQueue = std::queue<Index>;

    std::unordered_map<KeyType, IndexQueue> elements_;
    std::unordered_map<KeyType, Position> keys_;
    std::multimap<Position, KeyType> sorted_keys_;

 public:
    bool full() const {return cache_size_ == keys_.size();}
    explicit belady_cache_t(size_t cache_size): cache_size_(cache_size){}

    bool lookupUpdate(const KeyType& key) {
        bool isHit = false;

        if (!keys_.contains(key)) {
            bool able_to_insert = true;
            if (full())
                able_to_insert = deleteElem(key);

            if (able_to_insert)
                insertElem(key);
        }
        else {
            isHit = true;
            updateElem(key);
        }

        return isHit;
    }

    void preloadData(const KeyType& key, const size_t index) {
        elements_[key].push(index);
    }

 private:
    void insertElem(const KeyType& key) {
        assert(keys_.size() < cache_size_ && "CACHE OVERFLOWED WITHOUT DELETION");
        if (!elements_[key].empty()) {
            elements_[key].pop();
        }

        size_t newPos = 0;
        if (elements_[key].empty())
            newPos = ULLONG_MAX;
        else
            newPos = elements_[key].front();

        keys_.insert(std::make_pair(key, newPos));
        sorted_keys_.insert(std::make_pair(newPos, key));
    }

    bool deleteElem(const KeyType& next_key) {
        auto it = std::prev(sorted_keys_.end());
        bool result = needDeletion(it->second, next_key);

        if (result) {
            keys_.erase(it->second);
            sorted_keys_.erase(it);
        }

        return result;
    }

    void updateElem(const KeyType& key) {
        assert(!elements_.empty() && "NO ELEMENTS");
        assert(keys_.contains(key) && "NON-EXISTING ELEMENT");

        Position oldPos = keys_.at(key);
        Position newPos = ULLONG_MAX;

        if (!elements_[key].empty()) {
            elements_[key].pop();
        }

        if (elements_[key].empty()) {
            keys_[key] = newPos;
        }
        else {
            newPos = elements_[key].front();
            keys_[key] = newPos;
        }

        auto range = sorted_keys_.equal_range(oldPos);
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second == key) {
                sorted_keys_.erase(it);
                break;
            }
        }

        sorted_keys_.insert(std::make_pair(newPos, key));
    }

    bool needDeletion(const KeyType& prev_key, const KeyType& next_key) {
        assert(keys_.contains(prev_key) && "NO KEY FOR DELETION");
        assert(elements_.contains(next_key) && "NO KEY IN ELEMENTS MAP");

        bool result = true;

        if (elements_[next_key].size() <= 1 || elements_[next_key].empty()) {
            result = false;
            elements_[next_key].pop();
        }
        else if (keys_[prev_key] < elements_[next_key].front()) {
            result = false;
            elements_[next_key].pop();
        }

        return result;
    }
};

} // namespace belady