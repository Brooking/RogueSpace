#include <iostream>
#include <memory>
#include "catch.hpp"
#include "location.h"

TEST_CASE("location_withDefaultHeapConstructor_shouldMakeMaxOnes", "[location]")
{
    // arrange
    // act
    Location* location = new Location();

    // assert
    REQUIRE(location->row() == INT_MAX);
    REQUIRE(location->cell() == INT_MAX);
}

TEST_CASE("location_withDefaultSharedConstructor_shouldMakeMaxOnes", "[location]")
{
    // arrange
    // act
    std::shared_ptr<Location> location = std::make_shared<Location>();

    // assert
    REQUIRE(location->row() == INT_MAX);
    REQUIRE(location->cell() == INT_MAX);
}

TEST_CASE("location_withDefaultStackConstructor_shouldMakeMaxOnes", "[location]")
{
    // arrange
    // act
    Location location;

    // assert
    REQUIRE(location.row() == INT_MAX);
    REQUIRE(location.cell() == INT_MAX);
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

TEST_CASE("location_withSameLocations_shouldBeEqual", "[location]")
{
    // arrange
    // act
    Location location1(2,5);
    Location location2(2,5);

    // assert
    REQUIRE(location1 == location2);
}

TEST_CASE("location_withDifferentLocations_shouldNotBeNotEqual", "[location]")
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
    Location location1(1,66);
    Location location2(1,65);

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

TEST_CASE("distance_withColocated_shouldMakeZero", "[location]")
{
    // arrange
    Location target(5,5);
    Location location(5,5);

    // act
    unsigned int distance = location.distance(target);

    // assert
    REQUIRE(distance == 0);
}

TEST_CASE("distance_withDiagonalClose_shouldMakeNonZero", "[location]")
{
    // arrange
    Location target(5,5);
    Location location(6,6);

    // act
    unsigned int distance = location.distance(target);

    // assert
    REQUIRE(distance == 1);
}

TEST_CASE("distance_withOrthogonalClose_shouldMakeNonZero", "[location]")
{
    // arrange
    Location target(5,5);
    Location location(6,5);

    // act
    unsigned int distance = location.distance(target);

    // assert
    REQUIRE(distance == 1);
}

TEST_CASE("distance_withOrthogonalFar_shouldMakeNonZero", "[location]")
{   
    // arrange
    Location target(5,5);
    Location location(5,10);

    // act
    unsigned int distance = location.distance(target);

    // assert
    REQUIRE(distance == 5);
}

TEST_CASE("distance_withDiagonalFar_shouldMakeNonZero", "[location]")
{
    // arrange
    Location target(5,5);
    Location location(11,12);

    // act
    unsigned int distance = location.distance(target);

    // assert
    REQUIRE(distance == 9);
}

TEST_CASE("closerAdjacentLocations_withDiagonalFar_shouldMakeThreeInChevron", "[location]")
{
    // arrange
    Location target(5,5);
    Location location(11,11);

    // act
    std::vector<Location> closer_adjacent_locations = location.closer_adjacent_locations(target);

    // assert
    REQUIRE(closer_adjacent_locations.size() == 3);
    REQUIRE(closer_adjacent_locations[0] == Location(10,10));
    REQUIRE(closer_adjacent_locations[1] == Location(10,11));
    REQUIRE(closer_adjacent_locations[2] == Location(11,10));
}

TEST_CASE("closerAdjacentLocations_withOrthogonalFar_shouldMakeThreeInLine", "[location]")
{
    // arrange
    Location target(5,5);
    Location location(5,11);

    // act
    std::vector<Location> closer_adjacent_locations = location.closer_adjacent_locations(target);

    // assert
    REQUIRE(closer_adjacent_locations.size() == 3);
    REQUIRE(closer_adjacent_locations[0] == Location(4,10));
    REQUIRE(closer_adjacent_locations[1] == Location(5,10));
    REQUIRE(closer_adjacent_locations[2] == Location(6,10));
}

TEST_CASE("isAdjacent_withSpots_shouldReturnProperly", "[location]")
{
    //    0  1  2  3  4
    // 0 NN NN NN NN NN
    // 1 NN AD AO AD NN
    // 2 NN AO XX AO NN
    // 3 NN AD AO AD NN
    // 4 NN NN NN NN NN


    // arrange
    Location this_location(2, 2);
    Location that_location;

    // act
    // assert
    bool diagonal;
    that_location = Location(0,0);
    REQUIRE(this_location.is_adjacent(that_location, diagonal) == false);
    REQUIRE(diagonal == false);

    that_location = Location(1,4);
    REQUIRE(this_location.is_adjacent(that_location, diagonal) == false);
    REQUIRE(diagonal == false);

    that_location = Location(1,2);
    REQUIRE(this_location.is_adjacent(that_location, diagonal) == true);
    REQUIRE(diagonal == false);

    that_location = Location(2,3);
    REQUIRE(this_location.is_adjacent(that_location, diagonal) == true);
    REQUIRE(diagonal == false);

    that_location = Location(3,2);
    REQUIRE(this_location.is_adjacent(that_location, diagonal) == true);
    REQUIRE(diagonal == false);

    that_location = Location(2,1);
    REQUIRE(this_location.is_adjacent(that_location, diagonal) == true);
    REQUIRE(diagonal == false);

    that_location = Location(1,3);
    REQUIRE(this_location.is_adjacent(that_location, diagonal) == true);
    REQUIRE(diagonal == true);

    that_location = Location(3,3);
    REQUIRE(this_location.is_adjacent(that_location, diagonal) == true);
    REQUIRE(diagonal == true);

    that_location = Location(3,1);
    REQUIRE(this_location.is_adjacent(that_location, diagonal) == true);
    REQUIRE(diagonal == true);

    that_location = Location(1,1);
    REQUIRE(this_location.is_adjacent(that_location, diagonal) == true);
    REQUIRE(diagonal == true);
}


