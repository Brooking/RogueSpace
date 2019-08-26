#include "catch.hpp"
#include <iostream>
#include "imap_mock.h"
#include "../world/location.h"
#include "pathfinder.h"

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
