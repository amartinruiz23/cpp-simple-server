#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream>

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
