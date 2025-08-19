#include <gtest/gtest.h>
#include "lfu_cache.hpp"

template<typename KeyType> KeyType slowGetPage(KeyType key) {
    return key;
}

TEST (LFUCacheMethods, IsCacheFullTest) {
    size_t cacheSize = 1;
    lfu::lfu_cache_t<int, int> cache{cacheSize};
    cache.lookupUpdate(slowGetPage<int>, 1);
    cache.lookupUpdate(slowGetPage<int>, 1);
    EXPECT_TRUE(cache.full());
}

TEST (LFUCacheMethods, IsNotCacheFullTest) {
    size_t cacheSize = 2;
    lfu::lfu_cache_t<int, int> cache{cacheSize};
    cache.lookupUpdate(slowGetPage<int>, 1);
    cache.lookupUpdate(slowGetPage<int>, 1);
    EXPECT_FALSE(cache.full());
}

TEST (LFUCacheMethods, InsertElemTest) {
    size_t cacheSize = 1;
    lfu::lfu_cache_t<int, int> cache{cacheSize};
    cache.lookupUpdate(slowGetPage<int>, 1);
    cache.lookupUpdate(slowGetPage<int>, 1);
    EXPECT_EQ(cache.retHits(), 1);
}

TEST (LFUCacheMethods, UpdateElemTest) {
    size_t cacheSize = 2;
    lfu::lfu_cache_t<int, int> cache{cacheSize};
    cache.lookupUpdate(slowGetPage<int>, 1);
    cache.lookupUpdate(slowGetPage<int>, 3);
    cache.lookupUpdate(slowGetPage<int>, 1);
    cache.lookupUpdate(slowGetPage<int>, 2);

    EXPECT_EQ(cache.retHits(), 1);
}

TEST (LFUCacheMethods, UpdateElemStressTest) {
    size_t cacheSize = 2;
    lfu::lfu_cache_t<int, int> cache{cacheSize};
    cache.lookupUpdate(slowGetPage<int>, 1);
    cache.lookupUpdate(slowGetPage<int>, 1);
    cache.lookupUpdate(slowGetPage<int>, 1);
    cache.lookupUpdate(slowGetPage<int>, 1);
    cache.lookupUpdate(slowGetPage<int>, 2);

    EXPECT_EQ(cache.retHits(), 3);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}