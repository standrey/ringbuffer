#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <thread>

#include "ringbuffer.h"

#define M_TO_STRING_WRAPPER(x) #x
#define M_TO_STRING(x) M_TO_STRING_WRAPPER(x)
#define M_SOURCE __FILE__ ":" M_TO_STRING(__LINE__)

class stopwatch {
  using clock_type = std::chrono::steady_clock;

public:
  stopwatch() {
    start_ = clock_type::now();
  }

  template<typename t_duration>
  t_duration elapsed_duration() const {
    using namespace std::chrono;

    auto delta = clock_type::now() - start_;
    return duration_cast<t_duration>(delta);
  }

private:
  clock_type::time_point start_;
};


class hash_calculator {
 public:
  template <typename t_value>
  void set(const t_value& _value) {
    digest_ = std::hash<t_value>()(_value) ^ (digest_ << 1);
  }

  size_t value() const { return digest_; }

 private:
  size_t digest_ = 0;
};

void pinthread(int cpu) {
    if (cpu < 0) {
        return;
    }
  
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu, &cpuset);

    int res = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    if (res != 0) {
        std::cerr << "pthread_setaffinity_no error no: " << res << "\n";
        exit(EXIT_FAILURE);
    }
}

void test() {

  using namespace ringbuffer;
  constexpr size_t k_count = 10'000'000;
  constexpr size_t k_size = 1024;

  ring_buffer<int> buffer(k_size);

  size_t producer_hash = 0;
  std::chrono::milliseconds producer_time;

  size_t consumer_hash = 0;
  std::chrono::milliseconds consumer_time;

  std::thread producer([&]() {
    hash_calculator hash;
    stopwatch watch;

        pinthread(0);

    for (size_t i = 0; i < k_count; ++i) {
      hash.set(i);

      while (!buffer.push(i)) {
        std::this_thread::yield();
      }
    }

    producer_time = watch.elapsed_duration<std::chrono::milliseconds>();
    producer_hash = hash.value();
  });

  std::thread consumer([&]() {
    hash_calculator hash;
    stopwatch watch;
        pinthread(1);

    for (size_t i = 0; i < k_count; ++i) {
      int value;

      while (!buffer.pop(value)) {
        std::this_thread::yield();
      }

      hash.set(value);
    }

    consumer_time = watch.elapsed_duration<std::chrono::milliseconds>();
    consumer_hash = hash.value();
  });

  producer.join();
  consumer.join();

  if (producer_hash != consumer_hash) {
    std::cerr << "Workers hash must be equal\n";
  } else {
    std::cout << "producer_time: " << producer_time.count() << "ms; "
              << "consumer_time: " << consumer_time.count() << "ms\n";
  }
}

int main(int argc, char* argv[]) {
  int i = 0;
  while (++i < 100) {
    test();
  }

  return 0;
}
