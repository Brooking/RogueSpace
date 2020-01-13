#include <iostream>
#include "catch.hpp"
#include "dijkstra.h"
#include "../iwall_map_mock.h"
#include "location.h"

TEST_CASE("dijkstra_withTinyField_shouldFill", "[dijkstra]")
{
    // from
    // v
    // 10 00
    //    ^
    //    to

    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/1,/*width*/2);
    std::vector<std::vector<unsigned int>> distance(
        map->height(), 
        std::vector<unsigned int>(
            map->width(), 
            0));

    // act
    Dijkstra::fill(distance, map, /*to*/Location(0,1), /*from*/Location(0,0));

    // assert
    REQUIRE(distance[0][0] == 10);
    REQUIRE(distance[0][1] == 0);
}

TEST_CASE("dijkstra_withSmallField_shouldFill", "[dijkstra][.]")
{
    // from
    // v
    // 38 34 30
    // 28 24 20
    // 24 14 10
    // 20 10 00
    //       ^
    //       to

    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/4,/*width*/3);
    std::vector<std::vector<unsigned int>> distance(
        map->height(), 
        std::vector<unsigned int>(
            map->width(), 
            0));

    // act
    Dijkstra::fill(distance, map, /*to*/Location(3,2), /*from*/Location(0,0));

    // assert
    REQUIRE(distance[0][0] == 38);
    REQUIRE(distance[0][1] == 34);
    REQUIRE(distance[0][2] == 30);
    REQUIRE(distance[1][0] == 28);
    REQUIRE(distance[1][1] == 24);
    REQUIRE(distance[1][2] == 20);
    REQUIRE(distance[2][0] == 24);
    REQUIRE(distance[2][1] == 14);
    REQUIRE(distance[2][2] == 10);
    REQUIRE(distance[3][0] == 20);
    REQUIRE(distance[3][1] == 10);
    REQUIRE(distance[3][2] == 0);
}

TEST_CASE("dijkstra_withWall_shouldWrap", "[dijkstra][.]")
{
    // from
    // v
    // 54 44 34 24 20
    // 44 XX XX XX 10
    // 40 30 20 10 00
    //             ^
    //             to

    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/3,/*width*/5);
    iWallMapMock* mock = dynamic_cast<iWallMapMock*>(map.get());
    mock->set_opaque(1,1,true);
    mock->set_opaque(2,1,true);
    mock->set_opaque(3,1,true);
    std::vector<std::vector<unsigned int>> distance(
        map->height(),
        std::vector<unsigned int>(
            map->width(),
            0));

    // act
    Dijkstra::fill(distance, map, /*to*/Location(2,4), /*from*/Location(0,0));

    // assert
    REQUIRE(distance[0][0] == 54);
    REQUIRE(distance[0][1] == 44);
    REQUIRE(distance[0][2] == 34);
    REQUIRE(distance[0][3] == 24);
    REQUIRE(distance[0][4] == 20);
    REQUIRE(distance[1][0] == 44);
    REQUIRE(distance[1][1] == UINT_MAX);
    REQUIRE(distance[1][2] == UINT_MAX);
    REQUIRE(distance[1][3] == UINT_MAX);
    REQUIRE(distance[1][4] == 10);
    REQUIRE(distance[2][0] == 40);
    REQUIRE(distance[2][1] == 30);
    REQUIRE(distance[2][2] == 20);
    REQUIRE(distance[2][3] == 10);
    REQUIRE(distance[2][4] == 0);
}

// Note: this test case is the same as a pathfinder unit test
TEST_CASE("dijkstra_withLWall_shouldWrapAround", "[dijkstra]")
{
    //    0  1  2  3  4
    // 0  @  .  .  .  .
    // 1  .  X  X  X  .
    // 2  .  X  .  .  .
    // 3  .  X  .  M  .
    // 4  .  X  .  .  .

    //    0  1  2  3  4
    // 0 00 10 20 30 40
    // 1 10 XX XX XX 44
    // 2 20 XX 68 58 54
    // 3 30 XX 72 68 64
    // 4 40 XX 82 78 74



    // arrange
    std::shared_ptr<iWallMapMock> map = std::make_shared<iWallMapMock>(/*height*/5,/*width*/5);
    map->set_opaque(1,1,true);
    map->set_opaque(2,1,true);
    map->set_opaque(3,1,true);
    map->set_opaque(4,1,true);
    map->set_opaque(1,2,true);
    map->set_opaque(1,3,true);

    std::vector<std::vector<unsigned int>> distance(
        map->height(),
        std::vector<unsigned int>(
            map->width(),
            0));

    // act
    Dijkstra::fill(distance, map, /*to*/Location(0,0), /*from*/Location(3,3));

    // assert
    REQUIRE(distance[0][0] == 0);
    REQUIRE(distance[0][1] == 10);
    REQUIRE(distance[0][2] == 20);
    REQUIRE(distance[0][3] == 30);
    REQUIRE(distance[0][4] == 40);
    REQUIRE(distance[1][0] == 10);
    REQUIRE(distance[1][1] == UINT_MAX);
    REQUIRE(distance[1][2] == UINT_MAX);
    REQUIRE(distance[1][3] == UINT_MAX);
    REQUIRE(distance[1][4] == 44);
    REQUIRE(distance[2][0] == 20);
    REQUIRE(distance[2][1] == UINT_MAX);
    REQUIRE(distance[2][2] == 68);
    REQUIRE(distance[2][3] == 58);
    REQUIRE(distance[2][4] == 54);
    REQUIRE(distance[3][0] == 30);
    REQUIRE(distance[3][1] == UINT_MAX);
    REQUIRE(distance[3][2] == 72);
    REQUIRE(distance[3][3] == 68);
    REQUIRE(distance[3][4] == 64);
    REQUIRE(distance[4][0] == 40);
    REQUIRE(distance[4][1] == UINT_MAX);
    REQUIRE(distance[4][2] == 82);
    REQUIRE(distance[4][3] == 78);
    REQUIRE(distance[4][4] == 74);
}
