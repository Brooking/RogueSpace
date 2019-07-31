#include <stdexcept>
#include "catch.hpp"
#include <iostream>
#include "../world/floor.h"

TEST_CASE("floor_withConstruction_shouldMakeFloor", "[floor]")
{
    // arrange
    // act
    Floor floor(1,2);

    // assert
    REQUIRE(floor.height() == 1);
    REQUIRE(floor.width() == 2);
    REQUIRE(floor.tile(Location(0,0))->where() == Location(0,0));
    REQUIRE(floor.tile(Location(0,1))->where() == Location(0,1));
}

TEST_CASE("floor_withZeroHeightConstruction_shouldThrow", "[floor]")
{
    // arrange
    // act
    bool threw = false;
    try
    {
        Floor floor(0,1);
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
        Floor floor(10,0);
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

TEST_CASE("floor_withNegativeHeightConstruction_shouldThrow", "[floor]")
{
    // arrange
    // act
    bool threw = false;
    try
    {
        Floor floor(-10,1);
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

TEST_CASE("floor_withNegativeWidthConstruction_shouldThrow", "[floor]")
{
    // arrange
    // act
    bool threw = false;
    try
    {
        Floor floor(10,-1);
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
    Floor floor(1,1);

    // act
    Tile* tile = floor.tile(Location(1,1));

    // assert
    REQUIRE(tile == nullptr);
}

TEST_CASE("floor_withNegativeTileFetch_shouldReturnNull", "[floor]")
{
    // arrange
    Floor floor(1,1);

    // act
    Tile* tile = floor.tile(Location(-1,-1));

    // assert
    REQUIRE(tile == nullptr);
}
