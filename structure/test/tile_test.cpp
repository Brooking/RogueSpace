#include "catch.hpp"
#include <iostream>
#include "tile.h"
#include "ithing_mock.h"

TEST_CASE("tile_withConstructor_shouldMakeTile", "[tile]")
{
    // arrange
    Location location(1,1);

    // act
    Tile tile(/*floor*/nullptr, location);

    // assert
    REQUIRE(tile.token() == UIToken::bare_floor);    
    REQUIRE(tile.where() == location);
    REQUIRE(tile.floor() == nullptr);
    REQUIRE(tile.how_full() == ContentSize::empty);
    REQUIRE(tile.num_things() == 0);
}

TEST_CASE("tile_withAdd_shouldAddThing", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(-1,2));
    iThingMock thing(UIToken::none, /*tile*/nullptr, ContentSize::small);

    // act
    bool addWorked = tile.add(&thing);

    // assert
    REQUIRE(addWorked == true);
    REQUIRE(tile.num_things() == 1);
    REQUIRE(tile[0]->token() == UIToken::none);
    REQUIRE(tile.how_full() == ContentSize::small);
}

TEST_CASE("tile_withTwoFullAdd_shouldNotAdd", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(-1,2));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::full);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool addWorked = tile.add(&thing2);

    // assert
    REQUIRE(addWorked == false);
    REQUIRE(tile.num_things() == 1);
    REQUIRE(tile[0]->token() == UIToken::none);
    REQUIRE(tile.how_full() == ContentSize::full);
}

TEST_CASE("tile_withSecondFullAdd_shouldNotAdd", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(-1,2));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::small);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool addWorked = tile.add(&thing2);

    // assert
    REQUIRE(addWorked == false);
    REQUIRE(tile.num_things() == 1);
    REQUIRE(tile[0]->token() == UIToken::none);
    REQUIRE(tile.how_full() == ContentSize::small);
}

TEST_CASE("tile_withFillingAdd_shouldAddThing", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(-1,2));
    iThingMock thing(UIToken::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool addWorked = tile.add(&thing);

    // assert
    REQUIRE(addWorked == true);
    REQUIRE(tile.num_things() == 1);
    REQUIRE(tile[0]->token() == UIToken::none);
    REQUIRE(tile.how_full() == ContentSize::full);
}

TEST_CASE("tile_withAddNull_shouldFail", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(2,4));

    // act
    bool addWorked = tile.add(nullptr);

    // assert
    REQUIRE(addWorked == false);
    REQUIRE(tile.num_things() == 0);
}

TEST_CASE("tile_withRemove_shouldRemoveThing", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(5,1));
    iThingMock thing(UIToken::none, /*tile*/nullptr);
    tile.add(&thing);

    // act
    bool remove_worked = tile.remove(&thing);

    // assert
    REQUIRE(remove_worked == true);
    REQUIRE(tile.num_things() == 0);
    REQUIRE(tile.how_full() == ContentSize::empty);
}

TEST_CASE("tile_withFullRemove_shouldRemoveThing", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(5,1));
    iThingMock thing(UIToken::none, /*tile*/nullptr, ContentSize::full);
    tile.add(&thing);

    // act
    bool remove_worked = tile.remove(&thing);

    // assert
    REQUIRE(remove_worked == true);
    REQUIRE(tile.num_things() == 0);
    REQUIRE(tile.how_full() == ContentSize::empty);
}

TEST_CASE("tile_withRemoveNull_shouldFailElegantly", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(7,25));

    // act
    bool removeWorked = tile.remove(nullptr);

    // assert
    REQUIRE(removeWorked == false);
    REQUIRE(tile.num_things() == 0);
}

TEST_CASE("tile_withRemoveInvalid_shouldFailElegantly", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(-10,12));
    iThingMock thing(UIToken::none, /*tile*/nullptr);

    // act
    bool removeWorked = tile.remove(&thing);

    // assert
    REQUIRE(removeWorked == false);
    REQUIRE(tile.num_things() == 0);
}

TEST_CASE("tile_withRemoveFirst_shouldRemove", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(10,-12));
    iThingMock thing1(UIToken::none, /*tile*/nullptr);
    iThingMock thing2(UIToken::test, /*tile*/nullptr);
    tile.add(&thing1);
    tile.add(&thing2);

    // act
    bool removeWorked = tile.remove(&thing1);

    // assert
    REQUIRE(removeWorked == true);
    REQUIRE(tile.num_things() == 1);
    REQUIRE(tile[0]->token() == UIToken::test);
}

TEST_CASE("tile_withRemoveSecond_shouldRemove", "[tile]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(10,-12));
    iThingMock thing1(UIToken::none, /*tile*/nullptr);
    iThingMock thing2(UIToken::test, /*tile*/nullptr);
    tile.add(&thing1);
    tile.add(&thing2);

    // act
    bool removeWorked = tile.remove(&thing2);

    // assert
    REQUIRE(removeWorked == true);
    REQUIRE(tile.num_things() == 1);
    REQUIRE(tile[0]->token() == UIToken::none);
}
