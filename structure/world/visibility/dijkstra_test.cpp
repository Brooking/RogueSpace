#include <iostream>
#include "catch.hpp"
#include "dijkstra.h"
#include "../iwall_map_mock.h"
#include "location.h"

TEST_CASE("djystra_withTinyField_shouldFill", "[dijkstra]")
{
    // vfrom
    // 1 0
    //   ^to

    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/1,/*width*/2);
    std::vector<std::vector<unsigned int>> distance(
        map->height(), 
        std::vector<unsigned int>(
            map->width(), 
            0));

    // act
    Dijkstra::fill(distance, map, /*from*/Location(0,0), /*to*/Location(0,1));

    // assert
    REQUIRE(distance[0][0] == 1);
    REQUIRE(distance[0][1] == 0);
}

TEST_CASE("djystra_withSmallField_shouldFill", "[dijkstra][.]")
{
    // vfrom
    // 3 3 3
    // 2 2 2
    // 2 1 1
    // 2 1 0
    //     ^to

    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/4,/*width*/3);
    std::vector<std::vector<unsigned int>> distance(
        map->height(), 
        std::vector<unsigned int>(
            map->width(), 
            0));

    // act
    Dijkstra::fill(distance, map, /*from*/Location(0,0), /*to*/Location(3,2));

    // assert
    REQUIRE(distance[0][0] == 3);
    REQUIRE(distance[0][1] == 3);
    REQUIRE(distance[0][2] == 3);
    REQUIRE(distance[1][0] == 2);
    REQUIRE(distance[1][1] == 2);
    REQUIRE(distance[1][2] == 2);
    REQUIRE(distance[2][0] == 2);
    REQUIRE(distance[2][1] == 1);
    REQUIRE(distance[2][2] == 1);
    REQUIRE(distance[3][0] == 2);
    REQUIRE(distance[3][1] == 1);
    REQUIRE(distance[3][2] == 0);
}

TEST_CASE("djystra_withWall_shouldWrap", "[dijkstra][.]")
{
    // vfrom
    // 5 4 3 2 2
    // 4 X X X 1
    // 4 3 2 1 0
    //         ^to

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
    Dijkstra::fill(distance, map, /*from*/Location(0,0), /*to*/Location(2,4));

    // assert
    REQUIRE(distance[0][0] == 5);
    REQUIRE(distance[0][1] == 4);
    REQUIRE(distance[0][2] == 3);
    REQUIRE(distance[0][3] == 2);
    REQUIRE(distance[0][4] == 2);
    REQUIRE(distance[1][0] == 4);
    REQUIRE(distance[1][1] == -1);
    REQUIRE(distance[1][2] == -1);
    REQUIRE(distance[1][3] == -1);
    REQUIRE(distance[1][4] == 1);
    REQUIRE(distance[2][0] == 4);
    REQUIRE(distance[2][1] == 3);
    REQUIRE(distance[2][2] == 2);
    REQUIRE(distance[2][3] == 1);
    REQUIRE(distance[2][4] == 0);
}
