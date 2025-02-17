#include <catch2/catch_test_macros.hpp>
#include "ringbuffer.h"

TEST_CASE( "Push/Pop ringbuffer test", "[ringbuffer]" ) {
    using T = int;
    ringbuffer::ring_buffer<T> ring(2u);

    T result_v;

    REQUIRE( ring.pop(result_v) == false );
    
    REQUIRE( ring.push(1) == true );
    REQUIRE( ring.push(2) == true );
    REQUIRE( ring.push(3) == false );


    REQUIRE( ring.pop(result_v) == true);
    REQUIRE( result_v == 1 );
    REQUIRE( ring.pop(result_v) == true );
    REQUIRE( result_v == 2 );
    REQUIRE( ring.pop(result_v) == false );
}

