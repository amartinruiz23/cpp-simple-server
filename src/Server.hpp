#ifndef SERVER_H
#define SERVER_H

#include <csignal>

#include "BindingSocket.hpp"
#include "ServerThreadPool.hpp"

const int BUFFER_SIZE = 30000;

class Server{

  friend class ServerThreadPool;

  BindingSocket* socket;

  ServerThreadPool tp;

  std::pair<int,std::string> accepter();

  void launch();



public:
  Server(int domain, int service, int protocol, int port,
    u_long interface, int bklg, std::size_t cache_size);

  ~Server();

};

#endif
