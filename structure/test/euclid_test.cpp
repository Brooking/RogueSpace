#include "catch.hpp"
#include <iostream>
#include "euclid.h"

TEST_CASE("distance_withColocated_shouldMakeZero", "[euclid]")
{
    // arrange
    Location target(5,5);
    Location location(5,5);

    // act
    int distance = euclid::distance(target, location);

    // assert
    REQUIRE(distance == 0);
}

TEST_CASE("distance_withDiagonalClose_shouldMakeNonZero", "[euclid]")
{
    // arrange
    Location target(5,5);
    Location location(6,6);

    // act
    int distance = euclid::distance(target, location);

    // assert
    REQUIRE(distance == 1);
}

TEST_CASE("distance_withOrthogonalClose_shouldMakeNonZero", "[euclid]")
{
    // arrange
    Location target(5,5);
    Location location(6,5);

    // act
    int distance = euclid::distance(target, location);

    // assert
    REQUIRE(distance == 1);
}

TEST_CASE("distance_withOrthogonalFar_shouldMakeNonZero", "[euclid]")
{
    // arrange
    Location target(5,5);
    Location location(5,10);

    // act
    int distance = euclid::distance(target, location);

    // assert
    REQUIRE(distance == 5);
}

TEST_CASE("distance_withDiagonalFar_shouldMakeNonZero", "[euclid]")
{
    // arrange
    Location target(5,5);
    Location location(11,12);

    // act
    int distance = euclid::distance(target, location);

    // assert
    REQUIRE(distance == 9);
}

TEST_CASE("closerAdjacnetLocations_withDiagonalFar_shouldMakeThreeInChevron", "[euclid]")
{
    // arrange
    Location target(5,5);
    Location location(11,11);

    // act
    std::vector<Location> closer_adjacent_locations = euclid::closer_adjacent_locations(target, location);

    // assert
    REQUIRE(closer_adjacent_locations.size() == 3);
    REQUIRE(closer_adjacent_locations[0] == Location(10,10));
    REQUIRE(closer_adjacent_locations[1] == Location(10,11));
    REQUIRE(closer_adjacent_locations[2] == Location(11,10));
}

TEST_CASE("closerAdjacnetLocations_withOrthogonalFar_shouldMakeThreeInLine", "[euclid]")
{
    // arrange
    Location target(5,5);
    Location location(5,11);

    // act
    std::vector<Location> closer_adjacent_locations = euclid::closer_adjacent_locations(target, location);

    // assert
    REQUIRE(closer_adjacent_locations.size() == 3);
    REQUIRE(closer_adjacent_locations[0] == Location(4,10));
    REQUIRE(closer_adjacent_locations[1] == Location(5,10));
    REQUIRE(closer_adjacent_locations[2] == Location(6,10));
}
