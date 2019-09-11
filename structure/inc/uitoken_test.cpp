#include <iostream>
#include <memory>
#include "catch.hpp"
#include "uitoken.h"

TEST_CASE("uitoken_withDefaultConstructor_shouldMakeDefault", "[uitoken]")
{
    // arrange
    // act
    UIToken token;

    // assert
    REQUIRE(token.token_type() == TokenType::none);
    REQUIRE(token.is_visible() == false);
    REQUIRE(token.has_been_seen() == false);
    REQUIRE(token.is_lit() == false);
    REQUIRE(token.wall_type() == WallType::pillar);
}

TEST_CASE("uitoken_withTypeConstructor_shouldMakeDefaultWithType", "[uitoken]")
{
    // arrange
    // act
    UIToken token(TokenType::dog);

    // assert
    REQUIRE(token.token_type() == TokenType::dog);
    REQUIRE(token.is_visible() == false);
    REQUIRE(token.has_been_seen() == false);
    REQUIRE(token.is_lit() == false);
    REQUIRE(token.wall_type() == WallType::pillar);
}

TEST_CASE("uitoken_withWallLessConstructor_shouldMakeToken", "[uitoken]")
{
    // arrange
    // act
    UIToken token(TokenType::rat, /*visible*/true, /*seen*/true, /*lit*/false);

    // assert
    REQUIRE(token.token_type() == TokenType::rat);
    REQUIRE(token.is_visible() == true);
    REQUIRE(token.has_been_seen() == true);
    REQUIRE(token.is_lit() == false);
    REQUIRE(token.wall_type() == WallType::pillar);
}

TEST_CASE("uitoken_withWallConstructor_shouldMakeToken", "[uitoken]")
{
    // arrange
    // act
    UIToken token(WallType::nswe, /*visible*/false, /*seen*/true, /*lit*/true);

    // assert
    REQUIRE(token.token_type() == TokenType::wall);
    REQUIRE(token.is_visible() == false);
    REQUIRE(token.has_been_seen() == true);
    REQUIRE(token.is_lit() == true);
    REQUIRE(token.wall_type() == WallType::nswe);
}

TEST_CASE("uitoken_withDefaultWallConstructor_shouldMakeToken", "[uitoken]")
{
    // arrange
    // act
    UIToken token(WallType::nsw);

    // assert
    REQUIRE(token.token_type() == TokenType::wall);
    REQUIRE(token.is_visible() == false);
    REQUIRE(token.has_been_seen() == false);
    REQUIRE(token.is_lit() == false);
    REQUIRE(token.wall_type() == WallType::nsw);
}

TEST_CASE("uitoken_withFullConstructor_shouldMakeToken", "[uitoken]")
{
    // arrange
    // act
    UIToken token(TokenType::floor, /*visible*/false, /*seen*/true, /*lit*/true);

    // assert
    REQUIRE(token.token_type() == TokenType::floor);
    REQUIRE(token.is_visible() == false);
    REQUIRE(token.has_been_seen() == true);
    REQUIRE(token.is_lit() == true);
    REQUIRE(token.wall_type() == WallType::pillar);
}

TEST_CASE("uitoken_withBadSeenFullConstructor_shouldFault", "[uitoken]")
{
    // arrange
    // act
    bool exception_thrown = false;
    try
    {
        UIToken token(TokenType::bee, /*visible*/true, /*seen*/false, /*lit*/true);
    }
    catch(const std::exception& e)
    {
        exception_thrown = true;;
    }

    // assert
    REQUIRE(exception_thrown);
}

TEST_CASE("uitoken_withBadSeenWallConstructor_shouldFault", "[uitoken]")
{
    // arrange
    // act
    bool exception_thrown = false;
    try
    {
        UIToken token(WallType::nw, /*visible*/true, /*seen*/false, /*lit*/true);
    }
    catch(const std::exception& e)
    {
        exception_thrown = true;;
    }

    // assert
    REQUIRE(exception_thrown);
}

TEST_CASE("uitoken_withWallConstructionWithFull_shouldFault", "[uitoken]")
{
    // arrange
    // act
    bool exception_thrown = false;
    try
    {
        UIToken token(TokenType::wall, /*visible*/true, /*seen*/true, /*lit*/false);
    }
    catch(const std::exception& e)
    {
        exception_thrown = true;;
    }

    // assert
    REQUIRE(exception_thrown);
}

TEST_CASE("uitoken_withWallConstructionWithType_shouldFault", "[uitoken]")
{
    // arrange
    // act
    bool exception_thrown = false;
    try
    {
        UIToken token(TokenType::wall);
    }
    catch(const std::exception& e)
    {
        exception_thrown = true;;
    }

    // assert
    REQUIRE(exception_thrown);
}

