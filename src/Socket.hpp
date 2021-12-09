#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream>

/*!
Generic socket class. It does not implement the connection process, as it is different
in the server side and in the client side. In this project only the first one will be
implemented, but a socket for the client side could also inherit from this class.
*/

class Socket{

  int sock;
  struct sockaddr_in address;

public:

    //! Socket constructor. For more information, check https://man7.org/linux/man-pages/man2/socket.2.html.
    /*!
    \param domain specifies the communicantion domain
    \param service specifies the communication semantics
    \param protocol specifies a particular protocol to be used with the socket
    \param port specifies the number of port that will be used
    \param interface specifies port interface
    */
    Socket(int domain, int service, int protocol, int port, u_long interface);

    //! Virtual connection function. Must be implemented as bind (server) or connect (client).
    /*!
    \param sock specifies the socket file descriptor for the connection
    \param service address specifies the adress struct for the connection
    */
    virtual int connect_to_network(int sock, struct sockaddr_in address) = 0; // Bind or connect

    //! Test function for the socket
    void test_sock();

    //! Getter function for the socket file descriptor
    /*!
    \return socket file descriptor
    */
    int get_sock();

    //! Getter function for the address struct
    /*!
    \return address struct
    */
    struct sockaddr_in get_address();

    //! Virtual default destructor
    virtual ~Socket() = default;
};

#endif
