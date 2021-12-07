#include "BindingSocket.hpp"

//Constructor
BindingSocket::BindingSocket(int domain, int service, int protocol, int port,
   u_long interface, int bklg): Socket(domain, service, protocol, port, interface) {

  // Stablish connection
  connection = connect_to_network(get_sock(), get_address());
  test_connection();

  backlog = bklg;
  start_listening();
  test_listening();

}

// Set connection
int BindingSocket::connect_to_network(int sock, struct sockaddr_in address){
  return bind(sock, (struct sockaddr*)&address, sizeof(address));
}

void BindingSocket::start_listening(){

  listening = listen(get_sock(), backlog);
}

// Test connection
void BindingSocket::test_connection(){
  if (connection < 0) {
    std::cout << "Failed to bind to specified port. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
}

void BindingSocket::test_listening(){
  if (listening < 0){
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
}

// Getter functions
int BindingSocket::get_connection(){
  return connection;
}

// Connection getter
int BindingSocket::get_listening(){
  return listening;
}
