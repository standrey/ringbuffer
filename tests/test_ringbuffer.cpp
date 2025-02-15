#include <catch2/catch_test_macros.hpp>
#include "ringbuffer.h"

TEST_CASE( "Push ringbuffer test", "[ringbuffer]" ) {
    ringbuffer::ring_buffer<int> ring(2u);
    REQUIRE( ring.push(1) == true );
    REQUIRE( ring.push(2) == true );
    REQUIRE( ring.push(3) == false );
}

