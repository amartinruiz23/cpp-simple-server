#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream>

/*!
Generic socket class. It does not implement the connection process, as it is different
in the server side and in the client side. In this proyect only the first one will be
implemented, but a socket for the client side could also inherit from this class.
*/
class Socket{

  int sock;
  struct sockaddr_in address;

public:
    // Constructor
    Socket(int domain, int service, int protocol, int port, u_long interface);

    // Virtual connection function
    virtual int connect_to_network(int sock, struct sockaddr_in address) = 0; // Bind or connect

    // Test functions
    void test_sock();

    // Getter funcionts
    int get_sock();
    struct sockaddr_in get_address();

    virtual ~Socket() = default;
};

#endif
