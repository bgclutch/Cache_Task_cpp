#include "belady_cache.hpp"
#include <iostream>

template <typename KeyType> KeyType slowGetPage(const KeyType key) {
    return key;
}

int main() {
    size_t cacheSize = 0;
    size_t elemCount = 0;
    std::cin >> cacheSize >> elemCount;

    if (cacheSize == 0 || !std::cin.good()) {
        std::cerr << "Cache size should be positive\n";
        return EXIT_FAILURE;
    }

    if (elemCount == 0 || !std::cin.good()) {
        std::cerr << "Elements should exist\n";
        return EXIT_FAILURE;
    }

    belady::belady_cache_t<int> cache{cacheSize};
    std::vector<int> test_data;

    for (size_t i = 0; i < elemCount; ++i) {
        int elem = 0;
        std::cin >> elem;
        if (!std::cin.good()) {
            std::cerr << "Try to run program again and input correct data\n";
            return EXIT_FAILURE;
        }
        int new_key = slowGetPage(elem);
        cache.preloadData(new_key, i);
        test_data.push_back(new_key);
    }

    size_t cacheHits = 0;

    for (auto key : test_data)
        cacheHits += cache.lookupUpdate(key);

    std::cout << cacheHits << std::endl;

    return EXIT_SUCCESS;
}