#include <iostream>
#include "catch.hpp"
#include "dijkstra.h"
#include "imap_mock.h"
#include "../world/location.h"

TEST_CASE("djystra_withTinyField_shouldFill", "[dijkstra][.]")
{
    // vfrom
    // 1 0
    //   ^to

    // arrange
    iMapMock map(/*width*/2,/*height*/1);
    std::vector<std::vector<int>> distance(map.get_height(), std::vector(map.get_width(), 0));

    // act
    dijkstra_fill(distance, &map, /*from*/Location(0,0), /*to*/Location(0,1));

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
    iMapMock map(/*width*/3,/*height*/4);
    std::vector<std::vector<int>> distance(map.get_height(), std::vector(map.get_width(), 0));

    // act
    dijkstra_fill(distance, &map, /*from*/Location(0,0), /*to*/Location(3,2));

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
    iMapMock map(/*width*/5,/*height*/3);
    map.set_opaque(1,1,true);
    map.set_opaque(2,1,true);
    map.set_opaque(3,1,true);
    std::vector<std::vector<int>> distance(map.get_height(), std::vector(map.get_width(), 0));

    // act
    dijkstra_fill(distance, &map, /*from*/Location(0,0), /*to*/Location(2,4));

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
