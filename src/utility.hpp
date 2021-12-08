#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <openssl/md5.h>
#include <iomanip>


std::vector<std::string> split(const std::string &s, char delim);

bool is_number(const std::string& s);

std::string hash(std::string str);

std::string get_cmd_option(int argc, char* argv[], const std::string& option);

#endif
