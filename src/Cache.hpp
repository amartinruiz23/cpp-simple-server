#ifndef CACHE_H
#define CACHE_H

#include <cstddef>
#include <list>
#include <mutex>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <limits>
#include <iostream>

template <typename Key, typename Value>

/*!
Least recently used cache class. A template class to be used with any types. For more information check https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)
*/
class Cache {

 public:

  // Type aliases
  using value_type = typename std::pair<Key, Value>;
  using value_it = typename std::list<value_type>::iterator;
  using operation_guard = typename std::lock_guard<std::mutex>;

  //! Cache constructor.
  /*!
  \param max_size specifies the maximum size of the cache. If 0, the cache size will be the maximum posible.
  */
  Cache(size_t max_size) : max_cache_size{max_size} {
    if (max_size == 0) {
      max_cache_size = std::numeric_limits<size_t>::max();
    }
  }


  //! Puts a key and its value in the cache
  /*!
  \param key specifies the key to be inserted
  \param value specifies the value to be inserted
  */
  void put(const Key& key, const Value& value) {
    operation_guard og{safe_op}; // Take the mutex
    auto it = cache_items_map.find(key); // Find the key in the map

    if (it == cache_items_map.end()) { // If the key was not in the map
      if (cache_items_map.size() + 1 > max_cache_size) { // If the actual size is the limit
        auto last = cache_items_list.crbegin(); // Remove the last element from cache

        cache_items_map.erase(last->first);
        cache_items_list.pop_back();
      }

      cache_items_list.push_front(std::make_pair(key, value)); // Add the item to the cache
      cache_items_map[key] = cache_items_list.begin();
    }
    else { // If the item was already in the map
      it->second->second = value;
      cache_items_list.splice(cache_items_list.cbegin(), cache_items_list,
                              it->second); // Take it to the front of the list
    }
  }

  //! Queries a value from the cache
  /*!
  \param key specifies the key to be queried
  */
  Value& get(const Key& key) {
    operation_guard og{safe_op}; // Take the mutex
    auto it = cache_items_map.find(key); // Find the key

    if (it == cache_items_map.end()) { // If the key was not in the cache
      throw std::range_error("No such key in the cache"); // Error
    }
    else { // If it was in the cache
      cache_items_list.splice(cache_items_list.begin(), cache_items_list,
                              it->second); // Take it to the front

      return it->second->second; // Return the corresponding item
    }
  }

  //! Queries if a value is in the cache
  /*!
  \param key specifies the key to be queried
  */
  bool exists(const Key& key) {
    operation_guard og{safe_op}; // Take the mutex

    return cache_items_map.find(key) != cache_items_map.end(); // Return if the key is in the map
  }

  //! Queries the current size of the cache
  size_t Size() {
    operation_guard og{safe_op}; // Take the mutex

    return cache_items_map.size(); // Return the size of the map
  }

  //! Clears the cache
  void clear(){
    operation_guard og{safe_op};

    cache_items_list.clear(); // Clear the item list
    cache_items_map.clear();  // Clear the map
  }

  //! Output operator. Writes the cache content
  friend std::ostream& operator<<(std::ostream& os, const Cache& c){

    for (auto it = c.cache_items_list.begin(); it != c.cache_items_list.end(); ++it){
      os << "(" << it->first <<", "<< it->second << ")\n";
    }
    return os;
  }

private:
  std::list<value_type> cache_items_list; // List of recently consulted elemets
  std::unordered_map<Key, value_it> cache_items_map; // Map with the elements in the list, to efficiently access with the key
  size_t max_cache_size; // Maximum size of the cache
  std::mutex safe_op; // Mutex to make thread-safe opperations

};

#endif
