#include "catch.hpp"
#include <iostream>
#include "hero.h"
#include "floor.h"
#include "ithing_mock.h"

TEST_CASE("hero_withConstruction_shouldCreate", "[hero]")
{
    // arrange
    // act
    Hero hero(/*tile*/nullptr);

    // assert
    REQUIRE(hero.token() == UIToken::hero);
    REQUIRE(hero.tile() == nullptr);
    REQUIRE(hero.where() == Location());
}

TEST_CASE("hero_withDefaultConstruction_shouldCreate", "[hero]")
{
    // arrange
    // act
    Hero hero;

    // assert
    REQUIRE(hero.token() == UIToken::hero);
    REQUIRE(hero.tile() == nullptr);
    REQUIRE(hero.where() == Location());
}

TEST_CASE("hero_withLocatedConstruction_shouldCreateInPlace", "[hero]")
{
    // arrange
    Location location(100,101);
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(/*floor*/nullptr, location);

    // act
    Hero hero(tile);

    // assert
    REQUIRE(hero.token() == UIToken::hero);
    REQUIRE(hero.tile() == tile);
    REQUIRE(hero.where() == location);
}

TEST_CASE("hero_withValidMove_shouldMove", "[hero]")
{
    // arrange
    Floor floor(1,2);
    Hero hero(floor.tile(Location(0,0)));

    // act
    bool moved = hero.move(Direction::East);

    // assert
    REQUIRE(moved == true);
    REQUIRE(hero.tile() == floor.tile(Location(0,1)));
}

TEST_CASE("hero_withUpOffMove_shouldNotMove", "[hero]")
{
    // arrange
    Floor floor(1,2);
    Hero hero(floor.tile(Location(0,0)));

    // act
    bool moved = hero.move(Direction::North);

    // assert
    REQUIRE(moved == false);
    REQUIRE(hero.tile() == floor.tile(Location(0,0)));
}

TEST_CASE("hero_withMoveIntoWall_shouldNotMove", "[hero]")
{
    // arrange
    Floor floor(1,2);
    Hero hero(floor.tile(Location(0,0)));
    iThingMock wall(UIToken::test, floor.tile(Location(0,1)), ContentSize::full);
    floor.tile(Location(0,1))->add(&wall);

    // act
    bool moved = hero.move(Direction::East);

    // assert
    REQUIRE(moved == false);
    REQUIRE(hero.tile() == floor.tile(Location(0,0)));
}

TEST_CASE("hero_withPlace_shouldBePlaced", "[hero]")
{
    // arrange
    Floor floor(1,2);
    Hero hero;

    // act
    Location location(0,1);
    bool placed = hero.place(floor.tile(location));

    // assert
    REQUIRE(placed == true);
    REQUIRE(hero.tile() == floor.tile(location));
    REQUIRE(hero.where() == location);
}

TEST_CASE("hero_withRePlace_shouldBePlaced", "[hero]")
{
    // arrange
    Floor floor(1,2);
    Hero hero(floor.tile(Location(0,0)));

    // act
    Location location(0,1);
    bool placed = hero.place(floor.tile(location));

    // assert
    REQUIRE(placed == true);
    REQUIRE(hero.tile() == floor.tile(location));
    REQUIRE(hero.where() == location);
}

TEST_CASE("hero_withInvalidPlace_shouldNotBePlaced", "[hero]")
{
    // arrange
    Floor floor(1,2);
    Hero hero;

    // act
    Location location(0,2);
    bool placed = hero.place(floor.tile(location));

    // assert
    REQUIRE(placed == false);
    REQUIRE(hero.tile() == nullptr);
    REQUIRE(hero.where() == Location());
}

