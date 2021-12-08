#ifndef SERVER_H
#define SERVER_H

#include <csignal>

#include "BindingSocket.hpp"
#include "ServerThreadPool.hpp"

const int BUFFER_SIZE = 30000;

/*!
Server class that manages the connection to the socket and the tasks received
*/
class Server{

  friend class ServerThreadPool;

  BindingSocket* socket;

  ServerThreadPool tp; // Thread pool for task processing

  std::pair<int,std::string> accepter(); // Gets the message from the socket

  void launch(); // Starts the server and loops ultil end signal received

public:

  //! Server constructor.
  /*!
  \param domain specifies the communicantion domain for the socket
  \param service specifies the communication semantics for the socket
  \param protocol specifies a particular protocol to be used with the socket
  \param port specifies the number of port that will be used for the socket
  \param interface specifies port interface for the socket
  \param bklg defines the maximum length to which the queue of pending connections may grow in the socket
  \param cache_size defines the size of the cache
  */
  Server(int domain, int service, int protocol, int port,
    u_long interface, int bklg, std::size_t cache_size);

  //! Server destructor.
  ~Server();

};

#endif
