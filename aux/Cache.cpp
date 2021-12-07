#include "Cache.hpp"

Cache<Key, Value>::Cache(std::size_t max_size) : max_cache_size{max_size} {
  if (max_size == 0) {
    max_cache_size = std::numeric_limits<std::size_t>::max();
  }
}

void Cache<Key, Value>::Put(const Key& key, const Value& value) {
  std::lock_guard<std::mutex> og{safe_op};
  auto it = cache_items_map.find(key);

  if (it == cache_items_map.end()) {
    if (cache_items_map.size() + 1 > max_cache_size) {
      // remove the last element from cache
      auto last = cache_items_list.crbegin();

      cache_items_map.erase(last->first);
      cache_items_list.pop_back();
    }

    cache_items_list.push_front(std::make_pair(key, value));
    cache_items_map[key] = cache_items_list.begin();
  }
  else {
    it->second->second = value;
    cache_items_list.splice(cache_items_list.cbegin(), cache_items_list, it->second);
  }
}

const Value& Cache<Key, Value>::Get(const Key& key) {
  std::lock_guard<std::mutex> og{safe_op};
  auto it = cache_items_map.find(key);

  if (it == cache_items_map.end()) {
    throw std::range_error("No such key in the cache");
  }
  else {
    cache_items_list.splice(cache_items_list.begin(), cache_items_list,
                            it->second);

    return it->second->second;
  }
}

bool Cache<Key, Value>::Exists(const Key& key) {
  std::lock_guard<std::mutex> og{safe_op};

  return cache_items_map.find(key) != cache_items_map.end();
}

std::size_t Cache<Key, Value>::Size() const {
  std::lock_guard<std::mutex> og{safe_op};

  return cache_items_map.size();
}
