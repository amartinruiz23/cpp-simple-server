#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread> // std::thread
#include <vector> // std::vector
#include <queue> // std::queue
#include <mutex> // std::mutex
#include <condition_variable> // std::condition_variable
#include <vector>

class ThreadPool {

 public:

   ThreadPool();

  ~ThreadPool();

  void queue_work(int fd, std::string& request);

 private:
  // This condition variable is used for the threads to wait until there is work
  // to do
  std::condition_variable_any work_queue_condition_variable;

  // We store the threads in a vector, so we can later stop them gracefully
  std::vector<std::thread> threads;

  // Mutex to protect workQueue
  std::mutex work_queue_mutex;

  // Queue of requests waiting to be processed
  std::queue<std::pair<int, std::string>> work_queue;

  // This will be set to true when the thread pool is shutting down. This tells
  // the threads to stop looping and finish
  bool done;

  // Function used by the threads to grab work from the queue
  void do_work();

  virtual void process_request(const std::pair<int, std::string>) = 0;

};

#endif
