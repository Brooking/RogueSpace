#include "catch.hpp"
#include <iostream>
#include "imap_mock.h"
#include "../world/location.h"
#include "pathfinder.h"

TEST_CASE("djystra_withSmallField_shouldFill", "[pathfinder]")
{
    // vfrom
    // 3 3 3
    // 2 2 2
    // 2 1 1
    // 2 1 0
    //     ^to

    // arrange
    iMapMock map(/*width*/3,/*height*/4);
    Pathfinder pathfinder(&map);
    std::vector<std::vector<int>> distance(map.get_height(), std::vector(map.get_width(), 0));

    // act
    pathfinder.fill(distance, /*from*/Location(0,0), /*to*/Location(3,2));

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

TEST_CASE("djystra_withWall_shouldWrap", "[pathfinder]")
{
    // vfrom
    // 5 4 3 2 2
    // 4 X X X 1
    // 4 3 2 1 0
    //         ^to

    // arrange
    iMapMock map(/*width*/5,/*height*/3);
    Pathfinder pathfinder(&map);
    map.set_opaque(1,1,true);
    map.set_opaque(2,1,true);
    map.set_opaque(3,1,true);
    std::vector<std::vector<int>> distance(map.get_height(), std::vector(map.get_width(), 0));

    // act
    pathfinder.fill(distance, /*from*/Location(0,0), /*to*/Location(2,4));

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

TEST_CASE("pathfinder_withWall_shouldWalkAround", "[pathfinder]")
{
    // @ 5 4 3 .
    // . X X X 2
    // . X . 1 .
    // . X . M . 
    // . X . . .        

    // arrange
    iMapMock map(/*width*/5,/*height*/5);
    Pathfinder pathfinder(&map);
    map.set_opaque(1,1,true);
    map.set_opaque(2,1,true);
    map.set_opaque(3,1,true);
    map.set_opaque(1,2,true);
    map.set_opaque(1,3,true);
    map.set_opaque(1,4,true);

    // act
    std::vector<Location> path = pathfinder.find_path(/*from*/Location(3,3), /*to*/Location(0,0));

    // assert
    REQUIRE(path.size() == 6);
    REQUIRE(path[0] == Location(2,3));
    REQUIRE(path[1] == Location(1,4));
    REQUIRE(path[2] == Location(0,3));
    REQUIRE(path[3] == Location(0,2));
    REQUIRE(path[4] == Location(0,1));
    REQUIRE(path[5] == Location(0,0));
}
