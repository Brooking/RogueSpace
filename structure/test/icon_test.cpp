#include <iostream>
#include "catch.hpp"
#include "../ui/icon.h"
#include "uitoken.h"

TEST_CASE("icon_withDefaultToken_shouldGetBlank", "[icon]")
{
    // arrange
    UIToken token(TokenType::dog);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == 'd');
    REQUIRE(icon.foreground_color() == io::Color::BLACK);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withVisibleDogToken_shouldGetcharacter", "[icon]")
{
    // arrange
    UIToken token(TokenType::dog, true, true, false);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == 'd');
    REQUIRE(icon.foreground_color() == io::Color::BRIGHT_CYAN);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withSeenBeeToken_shouldGetBlank", "[icon]")
{
    // arrange
    UIToken token(TokenType::bee, false, true, false);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == 'b');
    REQUIRE(icon.foreground_color() == io::Color::BLACK);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withLitRatToken_shouldGetRat", "[icon]")
{
    // arrange
    UIToken token(TokenType::rat, true, true, true);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == 'r');
    REQUIRE(icon.foreground_color() == io::Color::BRIGHT_RED);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withVisibleWallToken_shouldGetWhiteWall", "[icon]")
{
    // arrange
    UIToken token(WallType::nw, true, true, false);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == static_cast<unsigned int>(io::Character::WALL_NW));
    REQUIRE(icon.foreground_color() == io::Color::WHITE);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withSeenWallToken_shouldGetGrayWall", "[icon]")
{
    // arrange
    UIToken token(WallType::ne, false, true, false);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == static_cast<unsigned int>(io::Character::WALL_NE));
    REQUIRE(icon.foreground_color() == io::Color::BRIGHT_BLACK);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withLitVisibleWallToken_shouldGetYellowWall", "[icon]")
{
    // arrange
    UIToken token(WallType::nswe, true, true, true);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == static_cast<unsigned int>(io::Character::WALL_NSWE));
    REQUIRE(icon.foreground_color() == io::Color::YELLOW);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withLitSeenOutOfViewWallToken_shouldGetGray", "[icon]")
{
    // arrange
    UIToken token(WallType::n, false, true, true);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == static_cast<unsigned int>(io::Character::WALL_NS));
    REQUIRE(icon.foreground_color() == io::Color::BRIGHT_BLACK);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withLitUnseenOutOfViewWallToken_shouldGetBlack", "[icon]")
{
    // arrange
    UIToken token(WallType::e, false, false, true);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == static_cast<unsigned int>(io::Character::WALL_WE));
    REQUIRE(icon.foreground_color() == io::Color::BLACK);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withVisibleFloorToken_shouldGetWhiteFloor", "[icon]")
{
    // arrange
    UIToken token(TokenType::floor, true, true, false);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == static_cast<unsigned int>(io::Character::BULLET));
    REQUIRE(icon.foreground_color() == io::Color::WHITE);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withSeenFloorToken_shouldGetGrayFloor", "[icon]")
{
    // arrange
    UIToken token(TokenType::floor, false, true, false);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == static_cast<unsigned int>(io::Character::BULLET));
    REQUIRE(icon.foreground_color() == io::Color::BRIGHT_BLACK);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withLitVisibleFloorToken_shouldGetYellowFloor", "[icon]")
{
    // arrange
    UIToken token(TokenType::floor, true, true, true);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == static_cast<unsigned int>(io::Character::BULLET));
    REQUIRE(icon.foreground_color() == io::Color::YELLOW);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withLitSeenOutOfViewFloorToken_shouldGetGray", "[icon]")
{
    // arrange
    UIToken token(TokenType::floor, false, true, true);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == static_cast<unsigned int>(io::Character::BULLET));
    REQUIRE(icon.foreground_color() == io::Color::BRIGHT_BLACK);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}

TEST_CASE("icon_withLitUnseenOutOfViewFloorToken_shouldGetBlack", "[icon]")
{
    // arrange
    UIToken token(TokenType::floor, false, false, true);

    // act
    Icon icon(token);

    // assert
    REQUIRE(icon.symbol() == static_cast<unsigned int>(io::Character::BULLET));
    REQUIRE(icon.foreground_color() == io::Color::BLACK);
    REQUIRE(icon.background_color() == io::Color::BLACK);
}