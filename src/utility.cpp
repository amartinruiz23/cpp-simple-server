#include "utility.hpp"

std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems; // Vector os substrings
  while (std::getline(ss, item, delim)) { //Get a substring to the next delimiter
    elems.push_back(item); // Save the substring
  }
  return elems; // Return the vector of substrings
}

bool is_number(const std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it; // Iterates until it finds a non-digit
    return !s.empty() && it == s.end(); // Return if the string is not empty and if the iterator reaches the end
}

std::string hash(std::string str){
  unsigned char result[MD5_DIGEST_LENGTH];
  MD5((unsigned char*)str.c_str(), str.size(), result); // Obtain the MD5 hash

  // Convert it to string
  std::ostringstream sout;
  sout<<std::hex<<std::setfill('0');
  for(long long c: result){
    sout<<std::setw(2)<<(long long)c;
 }
 return sout.str();
}

std::string get_cmd_option(int argc, const char* argv[], const std::string& option){
  std::string cmd = "";
  for( int i = 0; i < argc; ++i){ // Iterates through all the arguments
    std::string arg = argv[i];
    if(0 == arg.find(option)){ //If the option is at the begining of the argument
      if(i < argc -1){ // If there is another argument after the option
        cmd = argv[i + 1]; // The argument that will be returned is the one fater the option
      }
      return cmd;
    }
  }
  return cmd; // If the option is not found returns emptry string
}
