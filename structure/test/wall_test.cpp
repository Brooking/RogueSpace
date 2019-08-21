#include "catch.hpp"
#include <iostream>
#include "wall.h"
#include "tile.h"
#include "ithing_mock.h"

TEST_CASE("wall_withConstruction_shouldBeCreated", "[wall]")
{
    // arrange
    std::shared_ptr<Tile> tile(new Tile(/*floor*/nullptr, Location(0,0)));

    // act
    std::unique_ptr<Wall> wall(new Wall(tile));

    // assert
    REQUIRE(wall->token() == UIToken::visible_wall);
    REQUIRE(wall->tile() == tile);
}

TEST_CASE("wall_withConstructionNullTile_shouldThrow", "[wall]")
{
    // arrange
    // act
    bool threw = false;
    try
    {
        std::unique_ptr<Wall> wall(new Wall(/*tile*/nullptr));
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
    std::shared_ptr<Tile> tile(new Tile(/*floor*/nullptr, Location(0,0)));
    iThingMock thing(UIToken::test,nullptr);
    tile->add(&thing);

    // act
    bool threw = false;
    try
    {
        std::unique_ptr<Wall> wall(new Wall(tile));
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
