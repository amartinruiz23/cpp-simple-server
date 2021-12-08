#include "Socket.hpp"

// Constructor

const int TIMEOUT_SECONDS = 5;

Socket::Socket(int domain, int service, int protocol, int port, u_long interface){

  // Stablish socket
  sock = socket(domain, service, protocol);
  test_sock();

  // Stablish address structure
  address.sin_family = domain;
  address.sin_addr.s_addr = htonl(interface);
  address.sin_port = htons(port); // htons is necessary to convert a number to network byte order

  // Stablish timeout time of 5 seconds
  struct timeval tv;
  tv.tv_sec = TIMEOUT_SECONDS;
  tv.tv_usec = 0;
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

}

// Test functions

void Socket::test_sock(){
  if (sock < 0) {
    std::cout << "Failed to create socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
}

// Getter functions

int Socket::get_sock(){
  return sock;
}

struct sockaddr_in Socket::get_address(){
  return address;
}
