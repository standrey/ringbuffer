#include <atomic>
#include <cassert>
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <new>
#include <concepts>
#include <type_traits>

namespace ringbuffer {

template<typename T>
requires std::movable<T>
class ring_buffer {
public:
    explicit ring_buffer(size_t _capacity) : storage_(_capacity), capacity_(_capacity) {
        assert(_capacity != 0);
        if (_capacity == 0)  {
            throw std::runtime_error("ring_buffer capacity must be greater than zero");
        }
    }

    ring_buffer(const ring_buffer &) = delete;
    ring_buffer &operator=(const ring_buffer &) = delete;

    template <typename ... Args>
    bool push(Args && ... args) noexcept {
        if (sz_ == capacity_) {
            return false;
        }

        new (&storage_[tail_.load(std::memory_order_relaxed)]) T(std::forward<Args>(args)...);
        tail_.store(get_next_index(tail_), std::memory_order_release);
        sz_.fetch_add(1, std::memory_order_relaxed);
        return true;
    }

    bool pop(T& _value) noexcept {
        if (sz_ == 0) {
            return false;
        }

        auto cached_head = head_.load(std::memory_order_relaxed);
        _value = std::move(storage_[cached_head]);
        head_.store(get_next_index(cached_head), std::memory_order_relaxed);
        sz_.fetch_sub(1, std::memory_order_relaxed);
        return true;
    }

    size_t size() { return sz_.load(std::memory_order_relaxed); }
private:

    inline size_t get_next_index(size_t _slot) const noexcept {
        ++_slot;
        return (_slot == capacity_) ? 0 : _slot;
    }

    std::vector<T> storage_;
    size_t capacity_{ 0 };
    alignas(std::hardware_destructive_interference_size) std::atomic<size_t> sz_{ 0 };
    alignas(std::hardware_destructive_interference_size) std::atomic<size_t> head_{ 0 };
    alignas(std::hardware_destructive_interference_size) std::atomic<size_t> tail_{ 0 };
};

} // ringbuffer

