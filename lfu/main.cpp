#include <iostream>
#include <vector>
#include "lfu_cache.hpp"

template<typename KeyType, typename ValueType> ValueType slowGetPage(const KeyType key) {
    return static_cast<ValueType>(key);
}

int main() {
    size_t cacheSize, elemCount;
    std::cin >> cacheSize >> elemCount;

    lfu::lfu_cache_t<int, int> cache{cacheSize};

    if (cacheSize <= 0 || std::cin.bad()) {
        std::cerr << "Cache size should be positive" << std::endl;
        return EXIT_FAILURE;
    }

    if (elemCount <= 0 || std::cin.bad()) {
        std::cerr << "Elements should exist" << std::endl;
        return EXIT_FAILURE;
    }

    for (int i = 0; i < elemCount; ++i) {
        int elem;
        std::cin >> elem;
        if (std::cin.bad()) {
            std::cerr << "Try to run program again and input correct data" << std::endl;
            return EXIT_FAILURE;
        }
        cache.lookupUpdate(slowGetPage<int, int>, elem);
    }

    std::cout << cache.retHits() << std::endl;

    return EXIT_SUCCESS;
}