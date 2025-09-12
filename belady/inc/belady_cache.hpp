#pragma once

#include <iostream>
#include <climits>
#include <unordered_map>
#include <map>
#include <queue>
#include <vector>
#include <cassert>

namespace belady {

template <typename KeyType>
class belady_cache_t {
 private:
    size_t cache_size_ = 0;
    size_t hits_ = 0;

    using Index = size_t;
    using Position = size_t;
    using IndexQueue = std::queue<Index>;

    std::unordered_map<KeyType, IndexQueue> elements_;
    std::unordered_map<KeyType, Position> keys_;

 public:
    bool full() const {return cache_size_ == keys_.size();}
    size_t retHits() const {return hits_;}

    explicit belady_cache_t(size_t cache_size): cache_size_(cache_size){}

    template <typename DataType>
    void runBelady(const std::vector<DataType>& test_data, size_t elems) {
        assert(test_data.size() >= elems && "UNDERSIZED CACHE");
        for (size_t i = 0; i < elems; ++i) {
            KeyType key = test_data[i];
            if (!keys_.contains(key)) {
                bool able_to_insert = true;
                if (full())
                    able_to_insert = deleteElem(test_data[i]);

                if (able_to_insert)
                    insertElem(key);
            }
            else {
                ++hits_;
                updateElem(key);
            }
        }
    }

    void preloadData(const KeyType& key, const size_t index) {
        elements_[key].push(index);
    }

 private:
    void insertElem(const KeyType& key) {
        assert(keys_.size() < cache_size_ && "CACHE OVERFLOWED WITHOUT DELETION");
        size_t newPos;
        if (!elements_[key].empty()) {
            elements_[key].pop();
        }

        if (elements_[key].empty())
            newPos = ULLONG_MAX;
        else
            newPos = elements_[key].front();

        keys_.insert(std::make_pair(key, newPos));
    }

    bool deleteElem(const KeyType& next_key) {
        auto next_appearance = 0;
        auto key = keys_.begin();
        for (auto it = keys_.begin(); it != keys_.end(); ++it) {
            if (it->second == ULLONG_MAX) {
                key = it;
                break;
            }

            if (it->second > next_appearance) {
                next_appearance = it->second;
                key = it;
            }
        }

        bool result = needDeletion(key->first, next_key);

        if (result)
            keys_.erase(key);

        return result;
    }

    void updateElem(const KeyType& key) {
        assert(!elements_.empty() && "NO ELEMENTS");
        assert(keys_.contains(key) && "NON-EXISTING ELEMENT");

        if (!elements_[key].empty()) {
            elements_[key].pop();
        }

        if (elements_[key].empty())
            keys_[key] = ULLONG_MAX;
        else
            keys_[key] = elements_[key].front();
    }

    bool needDeletion(const KeyType& prev_key, const KeyType& next_key) {
        assert(keys_.contains(prev_key) && "NO KEY FOR DELETION");
        assert(elements_.contains(next_key) && "NO KEY IN ELEMENTS MAP");

        bool result = true;

        if (elements_[next_key].size() <= 1) {
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