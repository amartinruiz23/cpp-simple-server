#include "ServerThreadPool.hpp"

ServerThreadPool::ServerThreadPool(std::size_t cache_size):ThreadPool(),cache(cache_size){}

ServerThreadPool::~ServerThreadPool(){
  //~ThreadPool();
  std::cout<<cache<<std::endl;

}

void ServerThreadPool::processRequest(const std::pair<int, std::string> request){

    //std::thread::id this_id = std::this_thread::get_id();
    //std::cout<<"thread id: "<< this_id<<std::endl;
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
    std::vector<std::string> sections = split(request.second, ' ');

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
          //return Server::cache.Get(text);
          send(request.first, cache.Get(text).c_str(), cache.Get(text).size(), 0);
        } else {
          milisecs = std::stoi(sections[2]);
          std::this_thread::sleep_for(std::chrono::milliseconds(milisecs));
          std::string msg_hash = hash(text);
          cache.Put(text, msg_hash);
          //std::cout << hash(text) << std::endl;
          send(request.first, msg_hash.c_str(), msg_hash.size(), 0);
        }
      } else {
        //std::cout << "NO ES NÚMERO"<<std::endl;
        std::string inv = "INVALID";
        send(request.first, inv.c_str(), inv.size(), 0);
      }
    } else {
      std::string inv = "INVALID";
      send(request.first, inv.c_str(), inv.size(), 0);
    }
    //for (auto i : sections){
    //  std::cout << "SECTION: "<<i<<std::endl;
    //}

    //std::cout << msg << std::endl;
    //return msg;
    close(request.first);
}

void ServerThreadPool::cacheClear(){
  cache.clear();
}
