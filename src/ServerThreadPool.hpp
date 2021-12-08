#ifndef SERVER_THREAD_POOL_H
#define SERVER_THREAD_POOL_H

#include <unistd.h>
#include <chrono>
#include <sys/socket.h>

#include "ThreadPool.hpp"
#include "Cache.hpp"
#include "utility.hpp"

class ServerThreadPool: public ThreadPool{
public:

  ServerThreadPool(std::size_t cache_size);
  ~ServerThreadPool();

  void process_request(const std::pair<int, std::string> request);
  void cache_clear();

private:
  Cache<std::string, std::string> cache;
};

#endif
