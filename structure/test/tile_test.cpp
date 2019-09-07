#include <bits/stdc++.h>
#include <iostream>
#include "catch.hpp"
#include "ithing_mock.h"
#include "tile.h"

TEST_CASE("tile_withConstructor_shouldMakeTile", "[tile]")
{
    // arrange
    Location location(1,1);

    // act
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, location);

    // assert
    REQUIRE(tile->token().token_type() == TokenType::none);    
    REQUIRE(tile->where() == location);
    REQUIRE(tile->floor() == nullptr);
    REQUIRE(tile->how_full() == ContentSize::empty);
    REQUIRE(tile->num_things() == 0);
}

TEST_CASE("tile_withAdd_shouldAddThing", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(-1,2));
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr, ContentSize::small);

    // act
    bool addWorked = tile->add(thing);

    // assert
    REQUIRE(addWorked == true);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token().token_type() == TokenType::none);
    REQUIRE(tile->how_full() == ContentSize::small);
}

TEST_CASE("tile_withTwoFullAdd_shouldNotAdd", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(-1,2));
    std::shared_ptr<iThing> thing1 = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr, ContentSize::full);
    tile->add(thing1);
    std::shared_ptr<iThing> thing2 = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool addWorked = tile->add(thing2);

    // assert
    REQUIRE(addWorked == false);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token().token_type() == TokenType::none);
    REQUIRE(tile->how_full() == ContentSize::full);
}

TEST_CASE("tile_withSecondFullAdd_shouldNotAdd", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(-1,2));
    std::shared_ptr<iThing> thing1 = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr, ContentSize::small);
    tile->add(thing1);
    std::shared_ptr<iThing> thing2 = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool addWorked = tile->add(thing2);

    // assert
    REQUIRE(addWorked == false);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token().token_type() == TokenType::none);
    REQUIRE(tile->how_full() == ContentSize::small);
}

TEST_CASE("tile_withFillingAdd_shouldAddThing", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(-1,2));
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool addWorked = tile->add(thing);

    // assert
    REQUIRE(addWorked == true);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token().token_type() == TokenType::none);
    REQUIRE(tile->how_full() == ContentSize::full);
}

TEST_CASE("tile_withAddNull_shouldFail", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(2,4));

    // act
    bool addWorked = tile->add(nullptr);

    // assert
    REQUIRE(addWorked == false);
    REQUIRE(tile->num_things() == 0);
}

TEST_CASE("tile_withRemove_shouldRemoveThing", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(5,1));
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr);
    tile->add(thing);

    // act
    bool remove_worked = tile->remove(thing);

    // assert
    REQUIRE(remove_worked == true);
    REQUIRE(tile->num_things() == 0);
    REQUIRE(tile->how_full() == ContentSize::empty);
}

TEST_CASE("tile_withFullRemove_shouldRemoveThing", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(5,1));
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr, ContentSize::full);
    tile->add(thing);

    // act
    bool remove_worked = tile->remove(thing);

    // assert
    REQUIRE(remove_worked == true);
    REQUIRE(tile->num_things() == 0);
    REQUIRE(tile->how_full() == ContentSize::empty);
}

TEST_CASE("tile_withRemoveNull_shouldFailElegantly", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(7,25));

    // act
    bool removeWorked = tile->remove(nullptr);

    // assert
    REQUIRE(removeWorked == false);
    REQUIRE(tile->num_things() == 0);
}

TEST_CASE("tile_withRemoveInvalid_shouldFailElegantly", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(-10,12));
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr);

    // act
    bool removeWorked = tile->remove(thing);

    // assert
    REQUIRE(removeWorked == false);
    REQUIRE(tile->num_things() == 0);
}

TEST_CASE("tile_withRemoveFirst_shouldRemove", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(10,-12));
    std::shared_ptr<iThing> thing1 = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr);
    std::shared_ptr<iThing> thing2 = std::make_shared<iThingMock>(TokenType::test, /*tile*/nullptr);
    tile->add(thing1);
    tile->add(thing2);

    // act
    bool removeWorked = tile->remove(thing1);

    // assert
    REQUIRE(removeWorked == true);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token().token_type() == TokenType::test);
}

TEST_CASE("tile_withRemoveSecond_shouldRemove", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(10,-12));
    std::shared_ptr<iThing> thing1 = std::make_shared<iThingMock>(TokenType::none, /*tile*/nullptr);
    std::shared_ptr<iThing> thing2 = std::make_shared<iThingMock>(TokenType::test, /*tile*/nullptr);
    tile->add(thing1);
    tile->add(thing2);

    // act
    bool removeWorked = tile->remove(thing2);

    // assert
    REQUIRE(removeWorked == true);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token().token_type() == TokenType::none);
}

TEST_CASE("tile_heroCanSee_withNoFloor_shouldSayNo", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(10,12));

    // act
    bool hero_can_see = tile->hero_can_see();

    // assert
    REQUIRE(hero_can_see == false);
}

TEST_CASE("tile_heroCanSee_withNoHero_shouldSayNo", "[tile]")
{
    // arrange
    // todo make and add to floor
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(10,12));

    // act
    bool hero_can_see = tile->hero_can_see();

    // assert
    REQUIRE(hero_can_see == false);
}
