#include <cstddef>
#include <list>
#include <mutex>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <limits>
#include <iostream>

template <typename Key, typename Value>
class Cache {

 public:

  // Type aliases
  using value_type = typename std::pair<Key, Value>;
  using value_it = typename std::list<value_type>::iterator;
  using operation_guard = typename std::lock_guard<std::mutex>;

  Cache(size_t max_size) : max_cache_size{max_size} {
    if (max_size == 0) {
      max_cache_size = std::numeric_limits<size_t>::max();
    }
  }

  void put(const Key& key, const Value& value) {
    operation_guard og{safe_op};
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
      cache_items_list.splice(cache_items_list.cbegin(), cache_items_list,
                              it->second);
    }
  }

  Value& get(const Key& key) {
    operation_guard og{safe_op};
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

  bool exists(const Key& key) {
    operation_guard og{safe_op};

    return cache_items_map.find(key) != cache_items_map.end();
  }

  size_t Size() {
    operation_guard og{safe_op};

    return cache_items_map.size();
  }

  void clear(){
    operation_guard og{safe_op};

    cache_items_list.clear();
    cache_items_map.clear();
  }

  friend std::ostream& operator<<(std::ostream& os, const Cache& c){
    //operation_guard og{safe_op};

    for (auto it = c.cache_items_list.begin(); it != c.cache_items_list.end(); ++it){
      //std::cout << "AAA"<<std::endl;
      os << "(" << it->first <<", "<< it->second << ")\n";
    }
    return os;
  }

private:
  std::list<value_type> cache_items_list;
  std::unordered_map<Key, value_it> cache_items_map;
  size_t max_cache_size;
  std::mutex safe_op;

};
