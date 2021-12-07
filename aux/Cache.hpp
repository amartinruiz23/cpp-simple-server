//#include <cstddef>
#include <list>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <limits>

template <typename Key, typename Value>
class Cache {

  std::list<std::pair<Key, Value>> cache_items_list;
  std::unordered_map<Key, std::list<std::pair<Key, Value>>::iterator> cache_items_map;
  std::size_t max_cache_size;
  std::mutex safe_op;

public:

  Cache(std::size_t max_size);
  void Put(const Key& key, const Value& value);
  const Value& Cache::Get(const Key& key);
  bool Exists(const Key& key);
  std::size_t Size();

};
