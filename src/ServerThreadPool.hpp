#ifndef SERVER_THREAD_POOL_H
#define SERVER_THREAD_POOL_H

#include <unistd.h>
#include <chrono>
#include <sys/socket.h>

#include "ThreadPool.hpp"
#include "Cache.hpp"
#include "utility.hpp"

/*!
Thread pool class for the implemented server. It does implement the processing of petitions and includes the cache.
*/

class ServerThreadPool: public ThreadPool{
public:

  //! Server thread pool constructor.
  /*!
  \param cache_size specifies the maximum size of the cache. If 0, the cache size will be the maximum posible.
  */
  ServerThreadPool(std::size_t cache_size);

  //! Server thread pool constructor.
  ~ServerThreadPool();

  //! Process requests, returning the MD5 hash of the text and sleeping the specified time if the request is valid
  void process_request(const std::pair<int, std::string> request);

  //! Clears the cache
  void cache_clear();

private:
  Cache<std::string, std::string> cache; // Cache for saving last requests processed
};

#endif
