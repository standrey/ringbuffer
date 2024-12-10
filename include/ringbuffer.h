#include <atomic>
#include <cassert>
#include <cstddef>
#include <vector>
#include <stdexcept>

namespace ringbuffer {

template<typename T>
class ring_buffer {
public:
    explicit ring_buffer(size_t _capacity) : storage_(_capacity), capacity_(_capacity) {
        assert(_capacity != 0);
        if (_capacity == 0) throw std::runtime_error("ring_buffer capacity must be greate than zero");
    }

    template <typename ... Args>
    bool push(Args && ... args) noexcept {
        if (next_tail_ == head_.load(std::memory_order_acquire)) {
            return false;
        }

        new (&storage_[tail_.load(std::memory_order_relaxed)]) T(std::forward<Args>(args)...);
        tail_.store(next_tail_, std::memory_order_release);

        next_tail_ = get_next(next_tail_);
        return true;
    }

  bool pop(T& _value) noexcept {
    auto cached = head_.load(std::memory_order_relaxed);
    if (tail_.load(std::memory_order_acquire) == cached) { return false; }

    _value = std::move(storage_[cached]);
    head_.store(get_next(cached), std::memory_order_release);

    return true;
  }

private:

  inline size_t get_next(size_t _slot) const noexcept {
    ++_slot;
    return (_slot == capacity_) ? 0 : _slot;
  }

    std::vector<T> storage_;
    size_t capacity_ = { 0 };
    std::atomic<size_t> head_ = { 0 };
    std::atomic<size_t> tail_ = { 0 };
    size_t next_tail_ = tail_ + 1;
};

} // ringbuffer

