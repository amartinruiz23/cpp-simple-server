#include <unistd.h>
#include <chrono>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <sys/socket.h>

#include "ThreadPool.hpp"
#include "Cache.hpp"

//const std::size_t CACHE_SIZE = 10;

class ServerThreadPool: public ThreadPool{
public:

  ServerThreadPool(std::size_t cache_size);
  ~ServerThreadPool(); //TODO: ¿No necesario?

  void processRequest(const std::pair<int, std::string> request);
  void cacheClear();

private:
  Cache<std::string, std::string> cache;
};
