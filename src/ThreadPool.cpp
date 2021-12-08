#include "ThreadPool.hpp"

ThreadPool::ThreadPool() : done(false) {
  // This returns the number of threads supported by the system. If the
  // function can't figure out this information, it returns 0. 0 is not good,
  // so we create at least 1

  // Set the number of threads to the number supported by the system. If 0,
  // create at least 1.
  auto number_of_threads = std::thread::hardware_concurrency();
  if (number_of_threads == 0) {
    number_of_threads = 1;
  }

  for (unsigned i = 0; i < number_of_threads; ++i) {
    // The threads will execute the private member `doWork`. Note that we need
    // to pass a reference to the function (namespaced with the class name) as
    // the first argument, and the current object as second argument
    threads.push_back(std::thread(&ThreadPool::do_work, this));
  }
}

// The destructor joins all the threads so the program can exit gracefully.
// This will be executed if there is any exception (e.g. creating the threads)

ThreadPool::~ThreadPool() {
  // So threads know it's time to shut down
  done = true;

  // Wake up all the threads, so they can finish and be joined
  work_queue_condition_variable.notify_all();
  for (auto& thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

// This function will be called by the server every time there is a request
// that needs to be processed by the thread pool
void ThreadPool::queue_work(int fd, std::string& request) {
  // Grab the mutex
  std::lock_guard<std::mutex> g(work_queue_mutex);

  // Push the request to the queue
  work_queue.push(std::pair<int, std::string>(fd, request));

  // Notify one thread that there are requests to process
  work_queue_condition_variable.notify_one();
}

void ThreadPool::do_work() {
  // Loop while the queue is not destructing
  while (!done) {
    std::pair<int, std::string> request;

    // Create a scope, so we don't lock the queue for longer than necessary
    {
      std::unique_lock<std::mutex> g(work_queue_mutex);
      work_queue_condition_variable.wait(g, [&]{
        // Only wake up if there are elements in the queue or the program is
        // shutting down
        return !work_queue.empty() || done;
      });

      // If we are shutting down exit witout trying to process more work
      if (done) {
        break;
      }

      request = work_queue.front();
      work_queue.pop();
    }

    process_request(request);
  }
}
