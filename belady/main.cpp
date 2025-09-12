#include <iostream>
#include "belady_cache.hpp"

template <typename KeyType> KeyType slowGetPage(const KeyType key) {
    return key;
}

int main() {
size_t cacheSize, elemCount;
    std::cin >> cacheSize >> elemCount;

    belady::belady_cache_t<int> cache{cacheSize};

    if (cacheSize <= 0 || std::cin.bad()) {
        std::cerr << "Cache size should be positive" << std::endl;
        return EXIT_FAILURE;
    }

    if (elemCount <= 0 || std::cin.bad()) {
        std::cerr << "Elements should exist" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<int> test_data;


    for (int i = 0; i < elemCount; ++i) {
        int elem;
        std::cin >> elem;
        if (std::cin.bad()) {
            std::cerr << "Try to run program again and input correct data" << std::endl;
            return EXIT_FAILURE;
        }
        int new_key = slowGetPage(elem);
        cache.preloadData(new_key, i);
        test_data.push_back(new_key);
    }

    cache.runBelady(test_data, elemCount);


    std::cout << cache.retHits() << std::endl;

    return EXIT_SUCCESS;
}