#include "utility.hpp"

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

std::string get_cmd_option(int argc, char* argv[], const std::string& option){
    std::string cmd;
     for( int i = 0; i < argc; ++i)
     {
          std::string arg = argv[i];
          if(0 == arg.find(option))
          {
               std::size_t found = arg.find_first_of(option);
               cmd =arg.substr(found + 1);
               return cmd;
          }
     }
     return cmd;
}
