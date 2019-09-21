#include <iostream>
#include "catch.hpp"
#include "../iwall_map_mock.h"
#include "pathfinder.h"
#include "location.h"

TEST_CASE("pathfinder_withWall_shouldWalkAround", "[pathfinder]")
{
    //    0  1  2  3  4
    // 0  @  5  4  3  .
    // 1  .  X  X  X  2
    // 2  .  X  .  1  .
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
    Pathfinder pathfinder(map);
    map->set_opaque(1,1,true);
    map->set_opaque(2,1,true);
    map->set_opaque(3,1,true);
    map->set_opaque(4,1,true);
    map->set_opaque(1,2,true);
    map->set_opaque(1,3,true);

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
