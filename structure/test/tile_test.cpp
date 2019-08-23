#include "catch.hpp"
#include <iostream>
#include "tile.h"
#include "ithing_mock.h"

TEST_CASE("tile_withConstructor_shouldMakeTile", "[tile]")
{
    // arrange
    Location location(1,1);

    // act
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, location);

    // assert
    REQUIRE(tile->token() == UIToken::none);    
    REQUIRE(tile->where() == location);
    REQUIRE(tile->floor() == nullptr);
    REQUIRE(tile->how_full() == ContentSize::empty);
    REQUIRE(tile->num_things() == 0);
}

TEST_CASE("tile_withAdd_shouldAddThing", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(-1,2));
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr, ContentSize::small);

    // act
    bool addWorked = tile->add(thing);

    // assert
    REQUIRE(addWorked == true);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token() == UIToken::none);
    REQUIRE(tile->how_full() == ContentSize::small);
}

TEST_CASE("tile_withTwoFullAdd_shouldNotAdd", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(-1,2));
    std::shared_ptr<iThing> thing1 = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr, ContentSize::full);
    tile->add(thing1);
    std::shared_ptr<iThing> thing2 = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool addWorked = tile->add(thing2);

    // assert
    REQUIRE(addWorked == false);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token() == UIToken::none);
    REQUIRE(tile->how_full() == ContentSize::full);
}

TEST_CASE("tile_withSecondFullAdd_shouldNotAdd", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(-1,2));
    std::shared_ptr<iThing> thing1 = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr, ContentSize::small);
    tile->add(thing1);
    std::shared_ptr<iThing> thing2 = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool addWorked = tile->add(thing2);

    // assert
    REQUIRE(addWorked == false);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token() == UIToken::none);
    REQUIRE(tile->how_full() == ContentSize::small);
}

TEST_CASE("tile_withFillingAdd_shouldAddThing", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(-1,2));
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool addWorked = tile->add(thing);

    // assert
    REQUIRE(addWorked == true);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token() == UIToken::none);
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
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr);
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
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr, ContentSize::full);
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
    std::shared_ptr<iThing> thing = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr);

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
    std::shared_ptr<iThing> thing1 = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr);
    std::shared_ptr<iThing> thing2 = std::make_shared<iThingMock>(UIToken::test, /*tile*/nullptr);
    tile->add(thing1);
    tile->add(thing2);

    // act
    bool removeWorked = tile->remove(thing1);

    // assert
    REQUIRE(removeWorked == true);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token() == UIToken::test);
}

TEST_CASE("tile_withRemoveSecond_shouldRemove", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(10,-12));
    std::shared_ptr<iThing> thing1 = std::make_shared<iThingMock>(UIToken::none, /*tile*/nullptr);
    std::shared_ptr<iThing> thing2 = std::make_shared<iThingMock>(UIToken::test, /*tile*/nullptr);
    tile->add(thing1);
    tile->add(thing2);

    // act
    bool removeWorked = tile->remove(thing2);

    // assert
    REQUIRE(removeWorked == true);
    REQUIRE(tile->num_things() == 1);
    REQUIRE(tile->thing(0)->token() == UIToken::none);
}

TEST_CASE("tile_withNoLosSet_shouldSaySo", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(10,12));

    // act
    bool los_set = tile->los_has_been_calculated();

    // assert
    REQUIRE(los_set == false);
}

TEST_CASE("tile_withLosSet_shouldReturnLos", "[tile]")
{
    // arrange
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, Location(10,12));

    // act
    tile->add_los(Location(11,12));

    // assert
    REQUIRE(tile->los_has_been_calculated() == true);
    REQUIRE(tile->has_los(Location(11,12)) == true);
    REQUIRE(tile->has_los(Location(10,12)) == false);
}
