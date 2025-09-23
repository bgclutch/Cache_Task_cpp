#include <iostream>
#include <vector>
#include "lfu_cache.hpp"

template<typename KeyType, typename ValueType> ValueType slowGetPage(const KeyType key) {
    return static_cast<ValueType>(key);
}

int main() {
    size_t cacheSize = 0;
    size_t elemCount = 0;
    std::cin >> cacheSize >> elemCount;

    if (cacheSize == 0 || !std::cin.good()) {
        std::cerr << "Cache size should be positive" << std::endl;
        return EXIT_FAILURE;
    }

    if (elemCount == 0 || !std::cin.good()) {
        std::cerr << "Elements should exist" << std::endl;
        return EXIT_FAILURE;
    }

    lfu::lfu_cache_t<int, int> cache{cacheSize};
    size_t cacheHits = 0;

    for (size_t i = 0; i < elemCount; ++i) {
        int elem = 0;
        std::cin >> elem;
        if (!std::cin.good()) {
            std::cerr << std::endl << elem << std::endl;
            std::cerr << "Try to run program again and input correct data" << std::endl;
            return EXIT_FAILURE;
        }
        cacheHits += cache.lookupUpdate(slowGetPage<int, int>, elem);
    }

    std::cout << cacheHits << std::endl;

    return EXIT_SUCCESS;
}