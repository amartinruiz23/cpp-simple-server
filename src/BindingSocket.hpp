#ifndef BINDING_SOCKET_H
#define BINDING_SOCKET_H

#include "Socket.hpp"

/*!
Binding socket class. It inherits from the generic socket and implements the binding
process, used in the server side.
*/
class BindingSocket: public Socket{

  int connection;
  int backlog;
  int listening;

public:

  //Constructor
  BindingSocket(int domain, int service, int protocol, int port,
    u_long interface, int bklg); //:Socket(domain, service, protocol, port, interface);

  // Set connection
  int connect_to_network(int sock, struct sockaddr_in address);

  void start_listening();

  // Test functions
  void test_connection();
  void test_listening();

  int get_connection();
  int get_listening();

};

#endif
