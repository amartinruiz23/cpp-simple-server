bool is_number(const std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


std::vector<std::string> divide_string(std::string text){
  std::vector<std::string> sections{};
  std::string delimiter = " ";
  size_t pos = 0;

  while ((pos = text.find(delimiter)) != std::string::npos) {
    sections.push_back(text.substr(0, pos));
        text.erase(0, pos + delimiter.length());
  }
  sections.push_back(text);

  //std::cout<<"Sections lenght: "<<sections.size()<<std::endl;
  return sections;
}
