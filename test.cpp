#include <atomic>
#include <cassert>
#include <cstdlib>
#include <csignal>

static_assert(2 == ATOMIC_INT_LOCK_FREE, "this implementation does not guarantee that std::atomic<int> is always lock free.");

std::atomic<int> a = 0;
std::atomic<int> b = 0;

extern "C" void handler(int) {
    if (1 == a.load(std::memory_order_relaxed)) {
        std::atomic_signal_fence(std::memory_order_acquire);
        assert(1 == b.load(std::memory_order_relaxed));
    }

    std::exit(0);
}

int main() {
    std::signal(SIGTERM, &handler);

    b.store(1, std::memory_order_relaxed);
    std::atomic_signal_fence(std::memory_order_release);
    a.store(1, std::memory_order_relaxed);
}
