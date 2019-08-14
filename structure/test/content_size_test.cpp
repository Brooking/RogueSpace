#include "catch.hpp"
#include <iostream>
#include "tile.h"
#include "ithing_mock.h"

TEST_CASE("contentSize_with1small_shouldAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::small);

    // act
    bool allowed = tile.there_is_room(&thing1);

    // assert
    REQUIRE(allowed == true);
}

TEST_CASE("contentSize_with1large_shouldAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::large);

    // act
    bool allowed = tile.there_is_room(&thing1);

    // assert
    REQUIRE(allowed == true);
}

TEST_CASE("contentSize_with1full_shouldAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool allowed = tile.there_is_room(&thing1);

    // assert
    REQUIRE(allowed == true);
}

TEST_CASE("contentSize_with2small_shouldAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::small);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::small);

    // act
    bool allowed = tile.there_is_room(&thing2);

    // assert
    REQUIRE(allowed == true);
}

TEST_CASE("contentSize_with1smalland1large_shouldAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::small);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::large);

    // act
    bool allowed = tile.there_is_room(&thing2);

    // assert
    REQUIRE(allowed == true);
}

TEST_CASE("contentSize_with1smalland1full_shouldNotAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::small);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool allowed = tile.there_is_room(&thing2);

    // assert
    REQUIRE(allowed == false);
}

TEST_CASE("contentSize_with1large1small_shouldAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::large);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::small);

    // act
    bool allowed = tile.there_is_room(&thing2);

    // assert
    REQUIRE(allowed == true);
}

TEST_CASE("contentSize_with2large_shouldNotAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::large);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::large);

    // act
    bool allowed = tile.there_is_room(&thing2);

    // assert
    REQUIRE(allowed == false);
}

TEST_CASE("contentSize_with1large1full_shouldNotAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::large);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool allowed = tile.there_is_room(&thing2);

    // assert
    REQUIRE(allowed == false);
}

TEST_CASE("contentSize_with1full1small_shouldNotAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::full);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::small);

    // act
    bool allowed = tile.there_is_room(&thing2);

    // assert
    REQUIRE(allowed == false);
}

TEST_CASE("contentSize_with1full1large_shouldNotAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::full);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::large);

    // act
    bool allowed = tile.there_is_room(&thing2);

    // assert
    REQUIRE(allowed == false);
}

TEST_CASE("contentSize_with2full_shouldNotAllow", "[content_size]")
{
    // arrange
    Tile tile(/*floor*/nullptr, Location(0,0));
    iThingMock thing1(UIToken::none, /*tile*/nullptr, ContentSize::full);
    tile.add(&thing1);
    iThingMock thing2(UIToken::none, /*tile*/nullptr, ContentSize::full);

    // act
    bool allowed = tile.there_is_room(&thing2);

    // assert
    REQUIRE(allowed == false);
}