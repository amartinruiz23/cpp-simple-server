#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <openssl/md5.h>
#include <iomanip>
#include <unistd.h>

// Takes a string and a character delimiter as parameters and returns
// a vector of strings of the string parameters splitted by the
// delimiter character
std::vector<std::string> split(const std::string &s, char delim);

// Takes a string as parameter and returns if that string is a number
bool is_number(const std::string& s);

// Takes a string as a parameter and returns it's MD5 hash
std::string hash(std::string str);

// Takes the main parameters and a option string and returns the parameter
// that has been written after the option string
std::string get_cmd_option(int argc, const char* argv[], const std::string& option);

#endif
