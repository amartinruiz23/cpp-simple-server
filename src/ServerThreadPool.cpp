#include "ServerThreadPool.hpp"

ServerThreadPool::ServerThreadPool(std::size_t cache_size):ThreadPool(),cache(cache_size){}

ServerThreadPool::~ServerThreadPool(){
  std::cout<<cache<<std::endl; // Prints the cache
  std::cout << "Bye!" <<std::endl; // Prints goodbye message

}

void ServerThreadPool::process_request(const std::pair<int, std::string> request){

    std::string text;
    std::vector<std::string> sections = split(request.second, ' '); // Split text

    if (sections.size() == 3 && sections[0] == "get"){ // If the first word is get
      if (is_number(sections[2])){ // If the third word is a number
        text = sections[1]; // Text to be processed

        if (cache.exists(text)){ // If it is in the cache
          std::string msg_hash = cache.get(text); // Get the hash
          msg_hash.insert(msg_hash.end(), '\n'); // Add line break to the message
          send(request.first, msg_hash.c_str(), msg_hash.size(), 0); // Send the message to the port
        } else {
          int milisecs = std::stoi(sections[2]); // Get the number of milisecods to sleep
          std::this_thread::sleep_for(std::chrono::milliseconds(milisecs)); // sleep milisecods given
          std::string msg_hash = hash(text); // Get the hash of the text
          cache.put(text, msg_hash); // Put the hash at the cache
          msg_hash.insert(msg_hash.end(), '\n'); // Add line break to the message
          send(request.first, msg_hash.c_str(), msg_hash.size(), 0); // Send the message to the port
        }
      } else {
        std::string inv = "INVALID"; // If the third word is not a number send invalid message
        send(request.first, inv.c_str(), inv.size(), 0);
      }
    } else {
      std::string inv = "INVALID"; // If the first word is not get send invalid message
      send(request.first, inv.c_str(), inv.size(), 0);
    }

    close(request.first); // Close request file descriptor
}

void ServerThreadPool::cache_clear(){
  cache.clear(); // Clear the cache
}
