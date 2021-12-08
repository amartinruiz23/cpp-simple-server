#include "ServerThreadPool.hpp"

ServerThreadPool::ServerThreadPool(std::size_t cache_size):ThreadPool(),cache(cache_size){}

ServerThreadPool::~ServerThreadPool(){
  std::cout<<cache<<std::endl;
  std::cout << "Bye!" <<std::endl;

}

void ServerThreadPool::process_request(const std::pair<int, std::string> request){

    int milisecs = 5000;
    std::string text;
    std::vector<std::string> sections = split(request.second, ' ');

    if (sections.size() == 3 && sections[0] == "get"){
      if (is_number(sections[2])){ // si es número
        text = sections[1];

        if (cache.exists(text)){
          std::string msg_hash = cache.get(text);
          msg_hash.insert(msg_hash.end(), '\n');
          send(request.first, msg_hash.c_str(), msg_hash.size(), 0);
        } else {
          milisecs = std::stoi(sections[2]);
          std::this_thread::sleep_for(std::chrono::milliseconds(milisecs));
          std::string msg_hash = hash(text);
          cache.put(text, msg_hash);
          msg_hash.insert(msg_hash.end(), '\n');
          send(request.first, msg_hash.c_str(), msg_hash.size(), 0);
        }
      } else {
        std::string inv = "INVALID";
        send(request.first, inv.c_str(), inv.size(), 0);
      }
    } else {
      std::string inv = "INVALID";
      send(request.first, inv.c_str(), inv.size(), 0);
    }

    close(request.first);
}

void ServerThreadPool::cache_clear(){
  cache.clear();
}
