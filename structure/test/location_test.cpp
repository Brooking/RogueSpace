#include "catch.hpp"
#include <iostream>
#include "location.h"

TEST_CASE("location_withDefaultHeapConstructor_shouldMakeNegativeOnes", "[location]")
{
    // arrange
    // act
    Location* location = new Location();

    // assert
    REQUIRE(location->row() == -1);
    REQUIRE(location->cell() == -1);
}

TEST_CASE("location_withDefaultStackConstructor_shouldMakeNegativeOnes", "[location]")
{
    // arrange
    // act
    Location location;

    // assert
    REQUIRE(location.row() == -1);
    REQUIRE(location.cell() == -1);
}

TEST_CASE("location_withStackConstructor_shouldMakeSpecifiedCoordinates", "[location]")
{
    // arrange
    // act
    Location location(5,3);

    // assert
    REQUIRE(location.row() == 5);
    REQUIRE(location.cell() == 3);
}

TEST_CASE("location_withNegativeValuesToConstructor_shouldMakeSpecifiedCoordinates", "[location]")
{
    // arrange
    // act
    Location location(-10,-3);

    // assert
    REQUIRE(location.row() == -10);
    REQUIRE(location.cell() == -3);
}

TEST_CASE("location_withSameLocations_shouldBeEqual", "[location]")
{
    // arrange
    // act
    Location location1(2,5);
    Location location2(2,5);

    // assert
    REQUIRE(location1 == location2);
}

TEST_CASE("location_withSameLocations_shouldNotBeNotEqual", "[location]")
{
    // arrange
    // act
    Location location1(5,100);
    Location location2(5,100);

    // assert
    REQUIRE(!(location1 != location2));
}

TEST_CASE("location_withDifferentLocations_shouldNotBeEqual", "[location]")
{
    // arrange
    // act
    Location location1(-1,66);
    Location location2(-1,65);

    // assert
    REQUIRE(!(location1 == location2));
}

TEST_CASE("location_withDifferentLocations_shouldBeNotEqual", "[location]")
{
    // arrange
    // act
    Location location1(12,5);
    Location location2(21,5);

    // assert
    REQUIRE(location1 != location2);
}

TEST_CASE("location_withMoveNorth_shouldGoUpOneRow", "[location]")
{
    // arrange
    Location origin(1,1);

    // act
    Location destination = origin.apply_direction(Direction::North);

    // assert
    REQUIRE(destination == Location(0,1));
}

TEST_CASE("location_withMoveNorthEast_shouldGoUpOneRowAndRightOneCell", "[location]")
{
    // arrange
    Location origin(1,1);

    // act
    Location destination = origin.apply_direction(Direction::NorthEast);

    // assert
    REQUIRE(destination == Location(0,2));
}

TEST_CASE("location_withMoveEast_shouldGoRightOneCell", "[location]")
{
    // arrange
    Location origin(1,1);

    // act
    Location destination = origin.apply_direction(Direction::East);

    // assert
    REQUIRE(destination == Location(1,2));
}

TEST_CASE("location_withMoveSouthEast_shouldGoDownOneRowAndRightOneCell", "[location]")
{
    // arrange
    Location origin(1,1);

    // act
    Location destination = origin.apply_direction(Direction::SouthEast);

    // assert
    REQUIRE(destination == Location(2,2));
}

TEST_CASE("location_withMoveSouth_shouldGoDownOneRow", "[location]")
{
    // arrange
    Location origin(1,1);

    // act
    Location destination = origin.apply_direction(Direction::South);

    // assert
    REQUIRE(destination == Location(2,1));
}

TEST_CASE("location_withMoveSouthWest_shouldGoDownOneRowAndLeftOneCell", "[location]")
{
    // arrange
    Location origin(1,1);

    // act
    Location destination = origin.apply_direction(Direction::SouthWest);

    // assert
    REQUIRE(destination == Location(2,0));
}

TEST_CASE("location_withMoveWest_shouldGoLeftOneCell", "[location]")
{
    // arrange
    Location origin(1,1);

    // act
    Location destination = origin.apply_direction(Direction::West);

    // assert
    REQUIRE(destination == Location(1,0));
}

TEST_CASE("location_withMoveNorthWest_shouldGoUpOneRowAndLeftOneCell", "[location]")
{
    // arrange
    Location origin(1,1);

    // act
    Location destination = origin.apply_direction(Direction::NorthWest);

    // assert
    REQUIRE(destination == Location(0,0));
}

TEST_CASE("location_withMoveNone_shouldNotMove", "[location]")
{
    // arrange
    Location origin(1,1);

    // act
    Location destination = origin.apply_direction(Direction::none);

    // assert
    REQUIRE(destination == Location(1,1));
}

