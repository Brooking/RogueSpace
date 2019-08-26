#include "catch.hpp"
#include <iostream>
#include "original_shadow_cast.h"
#include "imap_mock.h"

TEST_CASE("iMapMock_withConstruction_shouldCreate", "[original_shadow_cast][.]")
{
    // arrange
    // act
    iMapMock map(/*width*/3,/*height*/4);

    // assert
    REQUIRE(map.get_width() == 3);
    REQUIRE(map.get_height() == 4);
    REQUIRE(map.has_los(0,0) == INT_MAX);
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
    REQUIRE(map.has_los(0,0) == INT_MAX);
    REQUIRE(map.is_opaque(2,2) == 1);
}

TEST_CASE("iMapMock_withLosSet_shouldCreate", "[original_shadow_cast]")
{
    // arrange
    iMapMock map(/*width*/3,/*height*/4);

    // act
    map.set_los(2,3,2*2);

    // assert
    REQUIRE(map.get_width() == 3);
    REQUIRE(map.get_height() == 4);
    REQUIRE(map.has_los(2,3) == 2);
    REQUIRE(map.is_opaque(2,2) == false);
}

TEST_CASE("originalShadowCast_withSmallMap_shouldShowAll", "[original_shadow_cast]")
{
    // ...
    // .@.
    // ...

    // arrange
    iMapMock map(/*width*/3,/*height*/3);

    // act
    do_fov(map, /*x*/1, /*y*/1);

    // assert
    REQUIRE(map.has_los(0,0) == 1);
    REQUIRE(map.has_los(0,1) == 1);
    REQUIRE(map.has_los(0,2) == 1);
    REQUIRE(map.has_los(1,0) == 1);
    REQUIRE(map.has_los(1,1) == 0);
    REQUIRE(map.has_los(1,2) == 1);
    REQUIRE(map.has_los(2,0) == 1);
    REQUIRE(map.has_los(2,1) == 1);
    REQUIRE(map.has_los(2,2) == 1);
}

TEST_CASE("originalShadowCast_withSmallishMap_shouldShowAll", "[original_shadow_cast]")
{
    // @1234
    // 11234
    // 22234
    // 33345
    // 44455

    // arrange
    iMapMock map(/*width*/5,/*height*/5);

    // act
    do_fov(map, /*x*/0, /*y*/0);

    // assert
    REQUIRE(map.has_los(0,0) == 0);
    REQUIRE(map.has_los(0,1) == 1);
    REQUIRE(map.has_los(0,2) == 2);
    REQUIRE(map.has_los(0,3) == 3);
    REQUIRE(map.has_los(0,4) == 4);

    REQUIRE(map.has_los(1,0) == 1);
    REQUIRE(map.has_los(1,1) == 1);
    REQUIRE(map.has_los(1,2) == 2);
    REQUIRE(map.has_los(1,3) == 3);
    REQUIRE(map.has_los(1,4) == 4);

    REQUIRE(map.has_los(2,0) == 2);
    REQUIRE(map.has_los(2,1) == 2);
    REQUIRE(map.has_los(2,2) == 2);
    REQUIRE(map.has_los(2,3) == 3);
    REQUIRE(map.has_los(2,4) == 4);

    REQUIRE(map.has_los(3,0) == 3);
    REQUIRE(map.has_los(3,1) == 3);
    REQUIRE(map.has_los(3,2) == 3);
    REQUIRE(map.has_los(3,3) == 4);
    REQUIRE(map.has_los(3,4) == 5);

    REQUIRE(map.has_los(4,0) == 4);
    REQUIRE(map.has_los(4,1) == 4);
    REQUIRE(map.has_los(4,2) == 4);
    REQUIRE(map.has_los(4,3) == 5);
    REQUIRE(map.has_los(4,4) == 5);
}

TEST_CASE("originalShadowCast_withFarPillarOnDiagonal_shouldShowSome", "[original_shadow_cast]")
{
    // @....
    // .....
    // ..#..
    // ...S.
    // ....S

    // @1234
    // 11234
    // 22234
    // 333X5
    // 4445X

 
    // arrange
    iMapMock map(/*width*/5,/*height*/5);
    map.set_opaque(2, 2, true);

    // act
    do_fov(map, /*x*/0, /*y*/0);

    // assert
    REQUIRE(map.has_los(0,0) == 0);
    REQUIRE(map.has_los(0,1) == 1);
    REQUIRE(map.has_los(0,2) == 2);
    REQUIRE(map.has_los(0,3) == 3);
    REQUIRE(map.has_los(0,4) == 4);

    REQUIRE(map.has_los(1,0) == 1);
    REQUIRE(map.has_los(1,1) == 1);
    REQUIRE(map.has_los(1,2) == 2);
    REQUIRE(map.has_los(1,3) == 3);
    REQUIRE(map.has_los(1,4) == 4);

    REQUIRE(map.has_los(2,0) == 2);
    REQUIRE(map.has_los(2,1) == 2);
    REQUIRE(map.has_los(2,2) == 2);
    REQUIRE(map.has_los(2,3) == 3);
    REQUIRE(map.has_los(2,4) == 4);

    REQUIRE(map.has_los(3,0) == 3);
    REQUIRE(map.has_los(3,1) == 3);
    REQUIRE(map.has_los(3,2) == 3);
    REQUIRE(map.has_los(3,3) == INT_MAX);
    REQUIRE(map.has_los(3,4) == 5);

    REQUIRE(map.has_los(4,0) == 4);
    REQUIRE(map.has_los(4,1) == 4);
    REQUIRE(map.has_los(4,2) == 4);
    REQUIRE(map.has_los(4,3) == 5);
    REQUIRE(map.has_los(4,4) == INT_MAX);
}

TEST_CASE("originalShadowCast_withFarPillarOnOblique_shouldShowSome", "[original_shadow_cast]")
{
    // .....
    // @....
    // ..#..
    // .....
    // ....S

    // 11234
    // 01234
    // 11234
    // 22234
    // 3334X

 
    // arrange
    iMapMock map(/*width*/5,/*height*/5);
    map.set_opaque(2, 2, true);

    // act
    do_fov(map, /*x*/0, /*y*/1);

    // assert
    REQUIRE(map.has_los(0,0) == 1);
    REQUIRE(map.has_los(0,1) == 0);
    REQUIRE(map.has_los(0,2) == 1);
    REQUIRE(map.has_los(0,3) == 2);
    REQUIRE(map.has_los(0,4) == 3);

    REQUIRE(map.has_los(1,0) == 1);
    REQUIRE(map.has_los(1,1) == 1);
    REQUIRE(map.has_los(1,2) == 1);
    REQUIRE(map.has_los(1,3) == 2);
    REQUIRE(map.has_los(1,4) == 3);

    REQUIRE(map.has_los(2,0) == 2);
    REQUIRE(map.has_los(2,1) == 2);
    REQUIRE(map.has_los(2,2) == 2);
    REQUIRE(map.has_los(2,3) == 2);
    REQUIRE(map.has_los(2,4) == 3);

    REQUIRE(map.has_los(3,0) == 3);
    REQUIRE(map.has_los(3,1) == 3);
    REQUIRE(map.has_los(3,2) == 3);
    REQUIRE(map.has_los(3,3) == 3);
    REQUIRE(map.has_los(3,4) == 4);

    REQUIRE(map.has_los(4,0) == 4);
    REQUIRE(map.has_los(4,1) == 4);
    REQUIRE(map.has_los(4,2) == 4);
    REQUIRE(map.has_los(4,3) == INT_MAX);
    REQUIRE(map.has_los(4,4) == 5);
}

TEST_CASE("originalShadowCast_withFarPillarOnOrthogonal_shouldShowSome", "[original_shadow_cast]")
{
    // .....
    // .....
    // @.#.S
    // .....
    // .....

    // 22234
    // 11234
    // 012XX
    // 11234
    // 22234

    // arrange
    iMapMock map(/*width*/5,/*height*/5);
    map.set_opaque(2, 2, true);

    // act
    do_fov(map, /*x*/0, /*y*/2);

    // assert
    REQUIRE(map.has_los(0,0) == 2);
    REQUIRE(map.has_los(0,1) == 1);
    REQUIRE(map.has_los(0,2) == 0);
    REQUIRE(map.has_los(0,3) == 1);
    REQUIRE(map.has_los(0,4) == 2);

    REQUIRE(map.has_los(1,0) == 2);
    REQUIRE(map.has_los(1,1) == 1);
    REQUIRE(map.has_los(1,2) == 1);
    REQUIRE(map.has_los(1,3) == 1);
    REQUIRE(map.has_los(1,4) == 2);

    REQUIRE(map.has_los(2,0) == 2);
    REQUIRE(map.has_los(2,1) == 2);
    REQUIRE(map.has_los(2,2) == 2);
    REQUIRE(map.has_los(2,3) == 2);
    REQUIRE(map.has_los(2,4) == 2);

    REQUIRE(map.has_los(3,0) == 3);
    REQUIRE(map.has_los(3,1) == 3);
    REQUIRE(map.has_los(3,2) == INT_MAX);
    REQUIRE(map.has_los(3,3) == 3);
    REQUIRE(map.has_los(3,4) == 3);

    REQUIRE(map.has_los(4,0) == 4);
    REQUIRE(map.has_los(4,1) == 4);
    REQUIRE(map.has_los(4,2) == INT_MAX);
    REQUIRE(map.has_los(4,3) == 4);
    REQUIRE(map.has_los(4,4) == 4);
}

TEST_CASE("originalShadowCast_withClosePillarOnDiagonal_shouldShowSome", "[original_shadow_cast]")
{
    // @..
    // .#.
    // ..S

    // arrange
    iMapMock map(/*width*/3,/*height*/3);
    map.set_opaque(1, 1, true);

    // act
    do_fov(map, /*x*/0, /*y*/0);

    // assert
    REQUIRE(map.has_los(0,0) == 0);
    REQUIRE(map.has_los(0,1) == 1);
    REQUIRE(map.has_los(0,2) == 2);

    REQUIRE(map.has_los(1,0) == 1);
    REQUIRE(map.has_los(1,1) == 1);
    REQUIRE(map.has_los(1,2) == 2);

    REQUIRE(map.has_los(2,0) == 2);
    REQUIRE(map.has_los(2,1) == 2);
    REQUIRE(map.has_los(2,2) == INT_MAX);
}

TEST_CASE("originalShadowCast_withClosePillarOnOrthogonal_shouldShowSome", "[original_shadow_cast]")
{
    // ...S
    // @#SS
    // ...S

    // arrange
    iMapMock map(/*width*/4,/*height*/3);
    map.set_opaque(1, 1, true);

    // act
    do_fov(map, /*x*/0, /*y*/1);

    // assert
    REQUIRE(map.has_los(0,0) == 1);
    REQUIRE(map.has_los(0,1) == 0);
    REQUIRE(map.has_los(0,2) == 1);

    REQUIRE(map.has_los(1,0) == 1);
    REQUIRE(map.has_los(1,1) == 1);
    REQUIRE(map.has_los(1,2) == 1);

    REQUIRE(map.has_los(2,0) == 2);
    REQUIRE(map.has_los(2,1) == INT_MAX);
    REQUIRE(map.has_los(2,2) == 2);

    REQUIRE(map.has_los(3,0) == INT_MAX);
    REQUIRE(map.has_los(3,1) == INT_MAX);
    REQUIRE(map.has_los(3,2) == INT_MAX);
}