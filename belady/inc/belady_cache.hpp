#pragma once

#include <iostream>
#include <climits>
#include <unordered_map>
#include <map>
#include <queue>
#include <vector>
#include <limits>

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
        for (size_t i = 0; i < elems; ++i) {
            KeyType key = test_data[i];
            if (!keys_.contains(key)) {
                if (full())
                    deleteElem();

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

    void deleteElem() {
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

        keys_.erase(key);
    }

    void updateElem(const KeyType& key) {
        if (!elements_[key].empty()) {
            elements_[key].pop();
        }

        if (elements_[key].empty())
            keys_[key] = ULLONG_MAX;
        else
            keys_[key] = elements_[key].front();
    }
};

} // namespace belady