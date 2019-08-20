#include "catch.hpp"
#include <iostream>
#include "original_shadow_cast.h"
#include "imap_mock.h"

TEST_CASE("iMapMock_withConstruction_shouldCreate", "[original_shadow_cast]")
{
    // arrange
    // act
    iMapMock map(/*width*/3,/*height*/4);

    // assert
    REQUIRE(map.get_width() == 3);
    REQUIRE(map.get_height() == 4);
    REQUIRE(map.has_los(0,0) == false);
    REQUIRE(map.is_opaque(0,0) == false);
}

TEST_CASE("iMapMock_withOpaqueSet_shouldCreate", "[original_shadow_cast]")
{
    // arrange
    iMapMock map(/*width*/3,/*height*/4);

    // act
    map.set_opaque(2,2,true);

    // assert
    REQUIRE(map.get_width() == 3);
    REQUIRE(map.get_height() == 4);
    REQUIRE(map.has_los(0,0) == false);
    REQUIRE(map.is_opaque(2,2) == true);
}

TEST_CASE("iMapMock_withLosSet_shouldCreate", "[original_shadow_cast]")
{
    // arrange
    iMapMock map(/*width*/3,/*height*/4);

    // act
    map.set_los(3,3,true);

    // assert
    REQUIRE(map.get_width() == 3);
    REQUIRE(map.get_height() == 4);
    REQUIRE(map.has_los(3,3) == true);
    REQUIRE(map.is_opaque(2,2) == false);
}

TEST_CASE("originalShadowCast_withSmallMap_shouldShowAll", "[original_shadow_cast]")
{
    // ...
    // .@.
    // ...

    // arrange
    iMapMock map(3,3);

    // act
    do_fov(map, /*x*/1, /*y*/1, /*radius*/2);

    // assert
    REQUIRE(map.has_los(0,0) == true);
    REQUIRE(map.has_los(0,1) == true);
    REQUIRE(map.has_los(0,2) == true);
    REQUIRE(map.has_los(1,0) == true);
    REQUIRE(map.has_los(1,1) == true);
    REQUIRE(map.has_los(1,2) == true);
    REQUIRE(map.has_los(2,0) == true);
    REQUIRE(map.has_los(2,1) == true);
    REQUIRE(map.has_los(2,2) == true);
}

TEST_CASE("originalShadowCast_withSmallishMap_shouldShowAll", "[original_shadow_cast]")
{
    // .....
    // .....
    // ..@..
    // .....
    // .....

    // arrange
    iMapMock map(5,5);

    // act
    do_fov(map, /*x*/2, /*y*/2, /*radius*/3);

    // assert
    REQUIRE(map.has_los(0,0) == true);
    REQUIRE(map.has_los(0,2) == true);
    REQUIRE(map.has_los(0,4) == true);

    REQUIRE(map.has_los(3,1) == true);
    REQUIRE(map.has_los(3,2) == true);
    REQUIRE(map.has_los(3,3) == true);

    REQUIRE(map.has_los(4,3) == true);
}

TEST_CASE("originalShadowCast_withFarPillarOnDiagonal_shouldShowSome", "[original_shadow_cast]")
{
    // @....
    // .....
    // ..#..
    // .....
    // ....S

    // arrange
    iMapMock map(5,5);
    map.set_opaque(2, 2, true);

    // act
    do_fov(map, /*x*/0, /*y*/0, /*radius*/10);

    // assert
    REQUIRE(map.has_los(0,0) == true);
    REQUIRE(map.has_los(0,1) == true);
    REQUIRE(map.has_los(0,2) == true);
    REQUIRE(map.has_los(0,3) == true);
    REQUIRE(map.has_los(0,4) == true);

    REQUIRE(map.has_los(1,0) == true);
    REQUIRE(map.has_los(1,1) == true);
    REQUIRE(map.has_los(1,2) == true);
    REQUIRE(map.has_los(1,3) == true);
    REQUIRE(map.has_los(1,4) == true);

    REQUIRE(map.has_los(2,0) == true);
    REQUIRE(map.has_los(2,1) == true);
    REQUIRE(map.has_los(2,2) == true);
    REQUIRE(map.has_los(2,3) == true);
    REQUIRE(map.has_los(2,4) == true);

    REQUIRE(map.has_los(3,0) == true);
    REQUIRE(map.has_los(3,1) == true);
    REQUIRE(map.has_los(3,2) == true);
    REQUIRE(map.has_los(3,3) == false);
    REQUIRE(map.has_los(3,4) == true);
}

TEST_CASE("originalShadowCast_withFarPillarOnOrthogonal_shouldShowSome", "[original_shadow_cast]")
{
    // .....
    // @.#.S
    // .....

    // arrange
    iMapMock map(5,3);
    map.set_opaque(/*row*/1, /*cell*/2, true);

    // act
    do_fov(map, /*x*/0, /*y*/1, /*radius*/10);

    // assert
    REQUIRE(map.has_los(0,0) == true);
    REQUIRE(map.has_los(0,1) == true);
    REQUIRE(map.has_los(0,2) == true);

    REQUIRE(map.has_los(1,0) == true);
    REQUIRE(map.has_los(1,1) == true);
    REQUIRE(map.has_los(1,2) == true);

    REQUIRE(map.has_los(2,0) == true);
    REQUIRE(map.has_los(2,1) == true);
    REQUIRE(map.has_los(2,2) == true);

    REQUIRE(map.has_los(3,0) == true);
    REQUIRE(map.has_los(3,1) == true);
    REQUIRE(map.has_los(3,2) == true);

    REQUIRE(map.has_los(4,0) == true);
    REQUIRE(map.has_los(4,1) == true); //?? should be blocked??
    REQUIRE(map.has_los(4,2) == true);
}

TEST_CASE("originalShadowCast_withClosePillarOnDiagonal_shouldShowSome", "[original_shadow_cast]")
{
    // @..
    // .#.
    // ..S

    // arrange
    iMapMock map(3,3);
    map.set_opaque(1, 1, true);

    // act
    do_fov(map, /*x*/0, /*y*/0, /*radius*/10);

    // assert
    REQUIRE(map.has_los(0,0) == true);
    REQUIRE(map.has_los(0,1) == true);
    REQUIRE(map.has_los(0,2) == true);

    REQUIRE(map.has_los(1,0) == true);
    REQUIRE(map.has_los(1,1) == true);
    REQUIRE(map.has_los(1,2) == true);

    REQUIRE(map.has_los(2,0) == true);
    REQUIRE(map.has_los(2,1) == true);
    REQUIRE(map.has_los(2,2) == false);
}

TEST_CASE("originalShadowCast_withClosePillarOnOrthogonal_shouldShowSome", "[original_shadow_cast]")
{
    // ...S
    // @#SS
    // ...S

    // arrange
    iMapMock map(4,3);
    map.set_opaque(/*row*/1, /*cell*/1, true);

    // act
    do_fov(map, /*x*/0, /*y*/1, /*radius*/10);

    // assert
    REQUIRE(map.has_los(0,0) == true);
    REQUIRE(map.has_los(0,1) == true);
    REQUIRE(map.has_los(0,2) == true);

    REQUIRE(map.has_los(1,0) == true);
    REQUIRE(map.has_los(1,1) == true);
    REQUIRE(map.has_los(1,2) == true);

    REQUIRE(map.has_los(2,0) == true);
    REQUIRE(map.has_los(2,1) == false);
    REQUIRE(map.has_los(2,2) == true);

    REQUIRE(map.has_los(3,0) == false);
    REQUIRE(map.has_los(3,1) == false);
    REQUIRE(map.has_los(3,2) == false);
}