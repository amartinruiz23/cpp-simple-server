#include <unistd.h>
#include <chrono>
#include <thread>
#include <vector>
#include <sstream>
#include <openssl/md5.h>
#include <iomanip>

#include "BindingSocket.hpp"
#include "Cache.hpp"

const int BUFFER_SIZE = 30000;
const std::size_t CACHE_SIZE = 10;

class Server{

  BindingSocket* socket;
  //char buffer[BUFFER_SIZE] = {0};
  int new_socket;
  Cache<std::string, std::string> cache;

  std::string accepter();
  std::string handdler(std::string msg);
  void responder(std::string msg);
  void launch();



public:
  Server(int domain, int service, int protocol, int port,
    u_long interface, int bklg, std::size_t cache_size);

  ~Server();



};
