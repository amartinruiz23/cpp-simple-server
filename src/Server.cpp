#include "Server.hpp"

bool is_number(const std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

std::string hash(std::string str){
  unsigned char result[MD5_DIGEST_LENGTH];
  MD5((unsigned char*)str.c_str(), str.size(), result);

  std::ostringstream sout;
  sout<<std::hex<<std::setfill('0');
  for(long long c: result){
    sout<<std::setw(2)<<(long long)c;
 }
 return sout.str();
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
    // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
  }
  return elems;
}

Server::Server(int domain, int service, int protocol, int port,
  u_long interface, int bklg, std::size_t cache_size):cache(cache_size){

  socket = new BindingSocket(domain, service, protocol, port, interface, bklg);
  //cache(cache_size);
  launch();
}

std::string Server::accepter(){
  struct sockaddr_in address = socket->get_address();
  auto addrlen = sizeof(sockaddr);
  new_socket = accept(socket->get_sock(), (struct sockaddr*)&address,
               (socklen_t *)&addrlen); // TODO: COMPROBAR QUE ES CORRECTA LA CONEXIÓN
  //std::cout << new_socket<<std::endl;
  //auto bytesRead = read(new_socket, buffer, BUFFER_SIZE);

  std::string output;
  output.resize(BUFFER_SIZE);

  auto bytes_received = read(new_socket, &output[0], BUFFER_SIZE-1);
  if (bytes_received<0) {
    std::cerr << "Failed to read data from socket.\n";
    return "";
  }

  output[bytes_received] = 0;
  output.resize(bytes_received + 1);
  //std::cout << output<<std::endl;
  return output;

}

std::string Server::handdler(std::string msg){

  int milisecs = 5000;
  std::string text;
  //std::string message = std::string(buffer);

  //bool primer_final = false;
  //for (int i = 0; i < 30000 && !primer_final; i++){
  //  std::cout << buffer[i]<< std::endl;
  //  if (buffer[i] == '\0'){
  //    primer_final = true;
  //    std::cout << "El final de la cadena"<<std::endl;
  //  }
  //}
  std::vector<std::string> sections = split(msg, ' ');

  bool invalid = false;
  if (sections.size() == 3 && sections[0] == "get"){
    //std::cout<<"TAMAÑO 3"<<std::endl;
    //std::cout<<"ES GET"<<std::endl;
    sections[2].resize(sections[2].size() - 2);
    //std::cout << "SECTIONS[2] " << sections[2] << std::endl;
    //std::cout << "IS NUMBER " << is_number(sections[2]) << std::endl;
    //std::cout << "SIZE " << sections[2].size() << std::endl;
    if (is_number(sections[2])){ // si es número
      text = sections[1];

      if (cache.Exists(text)){
        return cache.Get(text);
      } else {
        milisecs = std::stoi(sections[2]);
        std::this_thread::sleep_for(std::chrono::milliseconds(milisecs));
        std::string msg_hash = hash(text);
        cache.Put(text, msg_hash);
        //std::cout << hash(text) << std::endl;
        return msg_hash;
      }
    } else {
      //std::cout << "NO ES NÚMERO"<<std::endl;
      return "INVALID";
    }
  } else {
    return "INVALID";
  }
  //for (auto i : sections){
  //  std::cout << "SECTION: "<<i<<std::endl;
  //}

  //std::cout << msg << std::endl;
  //return msg;
}

void Server::responder(std::string msg){
  send(new_socket, msg.c_str(), msg.size(), 0);
  close(new_socket);
}

void Server::launch(){
  int i = 5;
  while(i){
    i--;
    //std::cout<<"-------"<<std::endl;
    std::string msg = accepter();
    std::string hash = handdler(msg);
    responder(hash);
    if (i == 2){
      std::cout<<cache<<std::endl;
      cache.clear();
    }
    //std::cout<<"-------"<<std::endl;
  }
  std::cout<<cache<<std::endl;
  close(socket->get_sock());
}

Server::~Server(){
  close(socket->get_sock());
  delete socket;
}
