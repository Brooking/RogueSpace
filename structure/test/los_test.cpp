#include <iostream>
#include "catch.hpp"
#include "los.h"

TEST_CASE("bresenham_withOrthogonal_shouldReturnRow", "[los]")
{
    // arrange
    // act
    std::vector<Location> locations = bresenham_los(1,1,1,3);

    // assert
    REQUIRE(locations.size() == 3);
    REQUIRE(locations[0] == Location(1,1));
    REQUIRE(locations[1] == Location(1,2));
    REQUIRE(locations[2] == Location(1,3));
}

TEST_CASE("bresenham_withDiagonal_shouldReturnDiagonal", "[los]")
{
    // arrange
    // act
    std::vector<Location> locations = bresenham_los(1,1,3,3);

    // assert
    REQUIRE(locations.size() == 3);
    REQUIRE(locations[0] == Location(1,1));
    REQUIRE(locations[1] == Location(2,2));
    REQUIRE(locations[2] == Location(3,3));
}

TEST_CASE("bresenham_withOblique_shouldReturnOblique", "[los]")
{
    // arrange
    // act
    std::vector<Location> locations = bresenham_los(5,5,3,0);

    // assert
    REQUIRE(locations.size() == 6);
    REQUIRE(locations[0] == Location(5,5));
    REQUIRE(locations[1] == Location(5,4));
    REQUIRE(locations[2] == Location(4,3));
    REQUIRE(locations[3] == Location(4,2));
    REQUIRE(locations[4] == Location(3,1));
    REQUIRE(locations[5] == Location(3,0));
}