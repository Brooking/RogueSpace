#include "catch.hpp"
#include <iostream>
#include "../world/hero.h"
#include "../world/floor.h"

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

TEST_CASE("hero_withLocatedConstruction_shouldCreateInPlace", "[hero]")
{
    // arrange
    Location location(100,101);
    Tile tile(/*floor*/nullptr, location);

    // act
    Hero hero(&tile);

    // assert
    REQUIRE(hero.token() == UIToken::hero);
    REQUIRE(hero.tile() == &tile);
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
