#include "catch.hpp"
#include <iostream>
#include "wall.h"
#include "tile.h"
#include "ithing_mock.h"

TEST_CASE("wall_withConstruction_shouldBeCreated", "[wall]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));

    // act
    Wall wall(&tile);

    // assert
    REQUIRE(wall.token() == UIToken::wall);
    REQUIRE(wall.tile() == &tile);
}

TEST_CASE("wall_withConstructionNullTile_shouldThrow", "[wall]")
{
    // arrange
    // act
    bool threw = false;
    try
    {
        Wall wall(/*tile*/nullptr);
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

TEST_CASE("wall_withConstructionPopulated_shouldThrow", "[wall]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing(UIToken::test,nullptr);
    tile.add(&thing);

    // act
    bool threw = false;
    try
    {
        Wall wall(&tile);
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
