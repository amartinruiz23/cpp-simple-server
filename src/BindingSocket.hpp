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

  //! Binding (server side) socket constructor. For more information, check https://man7.org/linux/man-pages/man2/socket.2.html.
  /*!
  \param domain specifies the communicantion domain
  \param service specifies the communication semantics
  \param protocol specifies a particular protocol to be used with the socket
  \param port specifies the number of port that will be used
  \param interface specifies port interface
  \param bklg defines the maximum length to which the queue of pending connections may grow
  */
  BindingSocket(int domain, int service, int protocol, int port,
    u_long interface, int bklg);

  //! Implements the connection to the network using the bind function
  /*!
  \param sock specifies the socket file descriptor for the connection
  \param service address specifies the adress struct for the connection
  */
  int connect_to_network(int sock, struct sockaddr_in address);

  //! Function to be called to start listening to the previously specified port
  void start_listening();

  //! Test function for the connection
  void test_connection();
  //! Test function for the port listening
  void test_listening();
  //! Getter for the connection binding, 0 on success, -1 on failure
  int get_connection();
  //! Getter for the listening, 0 on success, -1 on failure
  int get_listening();

};

#endif
