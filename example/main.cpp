#include <iostream>
#include "ringbuffer.h"

int main() {
    ringbuffer::ring_buffer<int> f(2);
    std::cout<<f.push(1)<<std::endl;
    std::cout<<f.push(2)<<std::endl;
    return 0;
}
