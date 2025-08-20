#pragma once

#include <iostream>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>

namespace belady {

template <typename KeyType>
class belady_cache_t {
 private:
    size_t cache_size_ = 0;
    size_t hits_ = 0;

    using Index = size_t;
    using IndexQueue = typename std::queue<Index>;

    std::unordered_map<KeyType, IndexQueue> elements_;
    std::unordered_set<KeyType> keys_;

 public:
    bool full() const {return cache_size_ == keys_.size();}
    size_t retHits() const {return hits_;}

    explicit belady_cache_t(size_t cache_size): cache_size_(cache_size){}

    template <typename DataType> void runBelady(const std::vector<DataType>& test_data, const size_t elems) {
        for (int i = 0; i < elems; ++i) {
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
        if (!elements_[key].empty())
            elements_[key].pop();
        keys_.insert(key);
    }

    void deleteElem() {
        auto next_appearance = INT_MIN;
        KeyType key;

        for (auto it = elements_.begin(); it != elements_.end(); ++it) {
            if (it->second.empty()) {
                key = it->first;
                break;
            }

            if (it->second.front() > next_appearance) {
                next_appearance = it->second.front();
                key = it->first;
            }
        }

        if (!elements_[key].empty())
            elements_[key].pop();
        keys_.erase(key);
    }

    void updateElem(const KeyType& key) {
        if (!elements_[key].empty())
            elements_[key].pop();
    }

};

} // namespace belady