#include <iostream>
#include "catch.hpp"
#include "ithing_mock.h"
#include "tile.h"
#include "wall.h"

TEST_CASE("wall_withConstruction_shouldBeCreated", "[wall]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(0,0));

    // act
    std::shared_ptr<Wall> wall = std::make_shared<Wall>();
    wall->place(tile);

    // assert
    REQUIRE(wall->token() == UIToken::visible_wall);
    REQUIRE(wall->tile() == tile);
}

TEST_CASE("wall_withPlaceOnPopulated_shouldFail", "[wall]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(0,0));
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(UIToken::test,nullptr);
    tile->add(thing);
    std::shared_ptr<Wall> wall = std::make_shared<Wall>();

    // act
    bool placed = wall->place(tile);

    // assert
    REQUIRE(placed == false);
    REQUIRE(wall->tile() == nullptr);
}
