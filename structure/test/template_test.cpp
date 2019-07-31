#include "catch.hpp"
#include <iostream>

TEST_CASE("testcase", "[category]")
{
    // set up

    // test
    INFO(1);
    REQUIRE(1 == 1);
}
