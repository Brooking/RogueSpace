#include <iostream>
#include <stdexcept>
#include "catch.hpp"
#include "floor.h"

TEST_CASE("floor_withConstruction_shouldMakeFloor", "[floor]")
{
    // arrange
    // act
    std::shared_ptr<Floor> floor = Floor::create(1,2);

    // assert
    REQUIRE(floor->height() == 1);
    REQUIRE(floor->width() == 2);
    REQUIRE(floor->tile(Location(0,0))->where() == Location(0,0));
    REQUIRE(floor->tile(Location(0,1))->where() == Location(0,1));
}

TEST_CASE("floor_withZeroHeightConstruction_shouldThrow", "[floor]")
{
    // arrange
    // act
    bool threw = false;
    try
    {
        std::shared_ptr<Floor> floor = Floor::create(0,1);
    }
    catch(const std::invalid_argument& e)
    {
        INFO(e.what());
        threw = true;
    }
    catch(const std::exception& e)
    {
        INFO(e.what());
    }

    // assert
    REQUIRE(threw == true);
}

TEST_CASE("floor_withZeroWidthConstruction_shouldThrow", "[floor]")
{
    // arrange
    // act
    bool threw = false;
    try
    {
        std::shared_ptr<Floor> floor = Floor::create(10,0);
    }
    catch(const std::invalid_argument& e)
    {
        INFO(e.what());
        threw = true;
    }
    catch(const std::exception& e)
    {
        INFO(e.what());
    }

    // assert
    REQUIRE(threw == true);
}

TEST_CASE("floor_withInvalidTileFetch_shouldReturnNull", "[floor]")
{
    // arrange
    std::shared_ptr<Floor> floor = Floor::create(1,1);

    // act
    std::shared_ptr<Tile> tile = floor->tile(Location(1,1));

    // assert
    REQUIRE(tile == nullptr);
}
