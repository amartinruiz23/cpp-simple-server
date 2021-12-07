#include "ThreadPool.h"

class ServerThreadPool: public ThreadPool{
public:

  ServerThreadPool();

  //~ServerThreadPool(); TODO: ¿No necesario?

  void processRequest(const std::pair<int, std::string> request);

};
