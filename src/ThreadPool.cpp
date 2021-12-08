#include "ThreadPool.hpp"

ThreadPool::ThreadPool() : done(false) {
  // Set the number of threads to the number supported by the system. If 0,
  // create at least 1.
  auto number_of_threads = std::thread::hardware_concurrency();
  if (number_of_threads == 0) {
    number_of_threads = 1;
  }

  for (unsigned i = 0; i < number_of_threads; ++i) {
    // Every thread executes the private member `doWork`.
    threads.push_back(std::thread(&ThreadPool::do_work, this));
  }
}

ThreadPool::~ThreadPool() {
  // Signals threads it's time to shut down
  done = true;

  // Wake up all the threads and join them
  work_queue_condition_variable.notify_all();
  for (auto& thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

// Function to be called by the server everty time there is a task to do
void ThreadPool::queue_work(int fd, std::string& request) {

  std::lock_guard<std::mutex> g(work_queue_mutex); // Grab the mutex

  work_queue.push(std::pair<int, std::string>(fd, request)); // Push the request to the queue

  work_queue_condition_variable.notify_one(); // Notify one thread that there are requests to process
}

void ThreadPool::do_work() {

  while (!done) { // While the queue is not destructing
    std::pair<int, std::string> request;

    // Create a scope for locking the queue de necessary time
    {
      std::unique_lock<std::mutex> g(work_queue_mutex);
      work_queue_condition_variable.wait(g, [&]{
        return !work_queue.empty() || done; // Wake up if there is something in the queue of shutting down
      });


      if (done) { // If shutting down, exit witout trying to process more work
        break;
      }

      request = work_queue.front();
      work_queue.pop();
    }

    process_request(request);
  }
}
