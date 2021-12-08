#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread> // std::thread
#include <vector> // std::vector
#include <queue> // std::queue
#include <mutex> // std::mutex
#include <condition_variable> // std::condition_variable
#include <vector>


/*!
Generic thread pool class. It does not implement the processing of the requests.
*/

class ThreadPool {

 public:

  //! Thread pool constructor
  ThreadPool();

  //! Thread pool destructor
  ~ThreadPool();

  //! Add work to the thread pool queue
  void queue_work(int fd, std::string& request);

 private:

   // Conditional variable used for the threads to wait until there is work to do
  std::condition_variable_any work_queue_condition_variable;

  std::vector<std::thread> threads; // Vector for the threads to be stored

  std::mutex work_queue_mutex; // Mutex to protect work queue

  std::queue<std::pair<int, std::string>> work_queue; // Queue of requests waiting to be processed

  bool done; // True when the thread pool is shutting done and the threads must join

  void do_work(); // Functions for the threads to grab work from the queue

  virtual void process_request(const std::pair<int, std::string>) = 0; // Not implemented request processing

};

#endif
