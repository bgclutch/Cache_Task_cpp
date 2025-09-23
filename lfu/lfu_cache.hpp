#pragma once

#include <list>
#include <unordered_map>
#include <cassert>

namespace lfu {

template <typename KeyType, typename ValueType>
class lfu_cache_t {
 private:
    using frequency = size_t;

    struct Node {
        ValueType value_;
        frequency frequency_;
    };

    using CacheList   = std::list<std::pair<KeyType, Node>>;
    using CacheListIt = CacheList::iterator;

    size_t cache_size_ = 0;
    const frequency basic_frequency = 1;
    frequency min_frequency_ = 0;

    std::unordered_map<frequency, CacheList> lists_;
    std::unordered_map<KeyType, CacheListIt> nodes_;

 public:
    bool full() const {return nodes_.size() == cache_size_;}

    explicit lfu_cache_t(size_t cache_size): cache_size_(cache_size){};

    template <typename Function> bool lookupUpdate(Function slowGetPage, const KeyType& key) {
        bool isHit = 0;

        if (!nodes_.contains(key)) {
            if (full())
                deleteElem();

            ValueType value = slowGetPage(key);

            insertElem(key, value);
            min_frequency_ = basic_frequency;
        }
        else {
            isHit = 1;
            updateElem(key);

            for (; min_frequency_ < cache_size_; ++min_frequency_) {
                if (lists_.contains(min_frequency_))
                    break;
            }
        }
        return isHit;
    }

 private:
    void addNewFrequency(const frequency new_frequency) {
        lists_.try_emplace(new_frequency);
    }

    void insertElem(const KeyType& key, const ValueType& value) {
        addNewFrequency(basic_frequency);
        assert(lists_.contains(basic_frequency) && "FAILED AT INSERT ELEM");
        auto& new_list = lists_.at(basic_frequency);

        Node new_node{value, basic_frequency};

        new_list.emplace_back(key, new_node);
        auto node_it = std::prev(new_list.end());

        nodes_.insert({key, node_it});
    }

    void deleteElem() {
        assert(lists_.contains(min_frequency_) && "FAILED AT DELETE ELEM");
        auto& least_frequently_list = lists_.at(min_frequency_);
        auto least_frequently_pair = least_frequently_list.front();

        least_frequently_list.pop_front();
        nodes_.erase(least_frequently_pair.first);
    }

    void updateElem(const KeyType& key) {
        assert(nodes_.contains(key) && "FAILED AT UPDATE ELEM ACCESS TO NODE");
        auto changing_node_it = nodes_.at(key);
        auto changing_node = changing_node_it->second;

        assert(lists_.contains(changing_node.frequency_) && "FAILED AT UPDATE ELEM ACCESS TO LIST");
        auto& prev_list = lists_.at(changing_node.frequency_);
        prev_list.erase(changing_node_it);

        if (prev_list.empty())
            lists_.erase(changing_node.frequency_);

        ++changing_node.frequency_;

        if (!lists_.contains(changing_node.frequency_))
            addNewFrequency(changing_node.frequency_);

        assert(lists_.contains(changing_node.frequency_) && "FAILED AT UPDATE ELEM UPDATING LIST");
        auto& new_list = lists_.at(changing_node.frequency_);

        new_list.emplace_back(key, changing_node);
        nodes_[key] = std::prev(new_list.end());
    }
};

} // namespace lfu
