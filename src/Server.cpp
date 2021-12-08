#include "Server.hpp"

extern sig_atomic_t finish;
extern sig_atomic_t flush;

Server::Server(int domain, int service, int protocol, int port,
  u_long interface, int bklg, std::size_t cache_size):tp(cache_size){

  socket = new BindingSocket(domain, service, protocol, port, interface, bklg); // Constructs the socket object
  launch(); // Launch the infinite loop
}

std::pair<int,std::string> Server::accepter(){
  struct sockaddr_in address = socket->get_address();
  auto addrlen = sizeof(sockaddr);
  int new_connection = accept(socket->get_sock(), (struct sockaddr*)&address,
               (socklen_t *)&addrlen); // Accept a message from the socket

  std::string output;
  output.resize(BUFFER_SIZE);

  auto bytes_received = read(new_connection, &output[0], BUFFER_SIZE-1);
  if (bytes_received<0) {
    return std::make_pair(new_connection,"");
  } // If the message received is not correct, return empty message

  output.resize(bytes_received - 1); // Resize the output string to the size of the message received
  return std::make_pair(new_connection, output);

}


void Server::launch(){

  while(!finish){ // While there is no finish signal
    if(flush){ // If there is a cache flush signal
      tp.cache_clear(); // Clear the cache
      flush = 0;
    }
    std::pair<int, std::string> request = accepter(); // Accept a request
    tp.queue_work(request.first, request.second); // Send the request to the thread pool
  }

  close(socket->get_sock()); // Close the socket file descriptor
}

Server::~Server(){
  delete socket; // Delete the socket
}
