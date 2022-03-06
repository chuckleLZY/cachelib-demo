#include "folly/init/Init.h"
#include "cachelib/allocator/CacheAllocator.h"

using Cache = facebook::cachelib::LruAllocator;
std::unique_ptr<Cache> cache;
facebook::cachelib::PoolId default_pool;

void initializeCache() {
  Cache::Config config;
  config
      .setCacheSize(1 * 1024 * 1024 * 1024) // 1 GB
      .setCacheName("My cache")
      .setAccessConfig({25, 10})
      .validate();
  cache = std::make_unique<Cache>(config);
  default_pool =
      cache->addPool("default", cache->getCacheMemoryStats().cacheSize);
}
int main(int argc, char** argv) {
  folly::init(&argc, &argv);

  initializeCache();

  destroyCache();
}
