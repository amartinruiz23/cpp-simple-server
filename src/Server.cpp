#include "Server.hpp"

extern sig_atomic_t finish;
extern sig_atomic_t flush;


Server::Server(int domain, int service, int protocol, int port,
  u_long interface, int bklg, std::size_t cache_size):tp(cache_size){

  socket = new BindingSocket(domain, service, protocol, port, interface, bklg);
  //cache(cache_size);
  launch();
}

std::pair<int,std::string> Server::accepter(){
  struct sockaddr_in address = socket->get_address();
  auto addrlen = sizeof(sockaddr);
  int new_connection = accept(socket->get_sock(), (struct sockaddr*)&address,
               (socklen_t *)&addrlen); // TODO: COMPROBAR QUE ES CORRECTA LA CONEXIÓN
  //std::cout << new_socket<<std::endl;
  //auto bytesRead = read(new_socket, buffer, BUFFER_SIZE);

  std::string output;
  output.resize(BUFFER_SIZE);

  auto bytes_received = read(new_connection, &output[0], BUFFER_SIZE-1);
  if (bytes_received<0) {
    //std::cerr << "Failed to read data from socket.\n";
    return std::make_pair(new_connection,"");
  }

  //output[bytes_received] = 0;
  output.resize(bytes_received - 1);
  //std::cout << output<<std::endl;
  return std::make_pair(new_connection, output);

}

//std::string Server::handdler(std::string msg){
//}

//void Server::responder(std::string msg){
//}

void Server::launch(){
  //int i = 5;

  while(!finish){
    if(flush){
      tp.cacheClear();
      flush = 0;
    }
    //std::cout<<"server finish: "<<finish<<std::endl;
    //i--;
    //std::cout<<"-------"<<std::endl;
    std::pair<int, std::string> request = accepter();
    tp.queueWork(request.first, request.second);
    //if (i == 2){
      //std::cout<<cache<<std::endl;
      //cache.clear();
    //}
    //std::cout<<"-------"<<std::endl;
  }
  close(socket->get_sock());
}

Server::~Server(){
  //close(socket->get_sock());
  delete socket;

}
