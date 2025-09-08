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

    clock_t begin = clock();
    cache.runBelady(test_data, elemCount);
    clock_t end = clock();

    double execution_time = double (end - begin) / CLOCKS_PER_SEC;
    double hits_percentage = (cache.retHits() / static_cast<double> (elemCount)) * 100;

    std::cout << "With cache size " << cacheSize << " and " << elemCount << " elems" << std::endl
              << "Hits getted: " << cache.retHits() << "(Hit ratio: " << hits_percentage << "%) with execution time " << execution_time << std::endl;

    return EXIT_SUCCESS;
}