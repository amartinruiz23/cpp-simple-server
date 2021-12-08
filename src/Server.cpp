#include "Server.hpp"

extern sig_atomic_t finish;
extern sig_atomic_t flush;


Server::Server(int domain, int service, int protocol, int port,
  u_long interface, int bklg, std::size_t cache_size):tp(cache_size){

  socket = new BindingSocket(domain, service, protocol, port, interface, bklg);
  launch();
}

std::pair<int,std::string> Server::accepter(){
  struct sockaddr_in address = socket->get_address();
  auto addrlen = sizeof(sockaddr);
  int new_connection = accept(socket->get_sock(), (struct sockaddr*)&address,
               (socklen_t *)&addrlen); // TODO: COMPROBAR QUE ES CORRECTA LA CONEXIÓN

  std::string output;
  output.resize(BUFFER_SIZE);

  auto bytes_received = read(new_connection, &output[0], BUFFER_SIZE-1);
  if (bytes_received<0) {
    return std::make_pair(new_connection,"");
  }

  output.resize(bytes_received - 1);
  return std::make_pair(new_connection, output);

}


void Server::launch(){

  while(!finish){
    if(flush){
      tp.cache_clear();
      flush = 0;
    }
    std::pair<int, std::string> request = accepter();
    tp.queue_work(request.first, request.second);
  }

  close(socket->get_sock());
}

Server::~Server(){
  delete socket;
}
