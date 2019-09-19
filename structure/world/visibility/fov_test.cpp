#include <iostream>
#include "catch.hpp"
#include "../iwall_map_mock.h"
#include "../ifov.h"
#include "fov.h"

class FovTestCallback : public iFov
{
public:
    FovTestCallback(unsigned int height, unsigned int width)
    : grid_(std::vector<std::vector<unsigned int>>(
        height,
        std::vector<unsigned int>(
            width,
            UINT_MAX)))
    {}
    void set_fov(unsigned int row, unsigned int cell, unsigned int distance) override
    {
        this->grid_[row][cell] = distance;
    }
    unsigned int get_fov(unsigned int row, unsigned int cell)
    {
        return this->grid_[row][cell];
    }

private:
    std::vector<std::vector<unsigned int>> grid_;
};

TEST_CASE("originalShadowCast_withSmallMap_shouldShowAll", "[fov]")
{
    // ...
    // .@.
    // ...

    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/3,/*width*/3);
    std::shared_ptr<iFov> fov = 
        std::make_shared<FovTestCallback>(map->height(), map->width());

    // act
    Fov::do_fov(fov, map, /*row*/1, /*cell*/1);

    // assert
    REQUIRE(fov->get_fov(0,0) == 1);
    REQUIRE(fov->get_fov(0,1) == 1);
    REQUIRE(fov->get_fov(0,2) == 1);
    REQUIRE(fov->get_fov(1,0) == 1);
    REQUIRE(fov->get_fov(1,1) == 0);
    REQUIRE(fov->get_fov(1,2) == 1);
    REQUIRE(fov->get_fov(2,0) == 1);
    REQUIRE(fov->get_fov(2,1) == 1);
    REQUIRE(fov->get_fov(2,2) == 1);
}

TEST_CASE("originalShadowCast_withSmallishMap_shouldShowAll", "[fov]")
{
    // @1234
    // 11234
    // 22234
    // 33345
    // 44455

    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/5,/*width*/5);
    std::shared_ptr<iFov> fov = 
        std::make_shared<FovTestCallback>(map->height(), map->width());

    // act
    Fov::do_fov(fov, map, /*row*/0, /*cell*/0);

    // assert
    REQUIRE(fov->get_fov(0,0) == 0);
    REQUIRE(fov->get_fov(0,1) == 1);
    REQUIRE(fov->get_fov(0,2) == 2);
    REQUIRE(fov->get_fov(0,3) == 3);
    REQUIRE(fov->get_fov(0,4) == 4);

    REQUIRE(fov->get_fov(1,0) == 1);
    REQUIRE(fov->get_fov(1,1) == 1);
    REQUIRE(fov->get_fov(1,2) == 2);
    REQUIRE(fov->get_fov(1,3) == 3);
    REQUIRE(fov->get_fov(1,4) == 4);

    REQUIRE(fov->get_fov(2,0) == 2);
    REQUIRE(fov->get_fov(2,1) == 2);
    REQUIRE(fov->get_fov(2,2) == 2);
    REQUIRE(fov->get_fov(2,3) == 3);
    REQUIRE(fov->get_fov(2,4) == 4);

    REQUIRE(fov->get_fov(3,0) == 3);
    REQUIRE(fov->get_fov(3,1) == 3);
    REQUIRE(fov->get_fov(3,2) == 3);
    REQUIRE(fov->get_fov(3,3) == 4);
    REQUIRE(fov->get_fov(3,4) == 5);

    REQUIRE(fov->get_fov(4,0) == 4);
    REQUIRE(fov->get_fov(4,1) == 4);
    REQUIRE(fov->get_fov(4,2) == 4);
    REQUIRE(fov->get_fov(4,3) == 5);
    REQUIRE(fov->get_fov(4,4) == 5);
}

TEST_CASE("originalShadowCast_withFarPillarOnDiagonal_shouldShowSome", "[fov]")
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
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/5,/*width*/5);
    map->set_opaque(2, 2, true);
    std::shared_ptr<iFov> fov = 
        std::make_shared<FovTestCallback>(map->height(), map->width());

    // act
    Fov::do_fov(fov, map, /*row*/0, /*cell*/0);

    // assert
    REQUIRE(fov->get_fov(0,0) == 0);
    REQUIRE(fov->get_fov(0,1) == 1);
    REQUIRE(fov->get_fov(0,2) == 2);
    REQUIRE(fov->get_fov(0,3) == 3);
    REQUIRE(fov->get_fov(0,4) == 4);

    REQUIRE(fov->get_fov(1,0) == 1);
    REQUIRE(fov->get_fov(1,1) == 1);
    REQUIRE(fov->get_fov(1,2) == 2);
    REQUIRE(fov->get_fov(1,3) == 3);
    REQUIRE(fov->get_fov(1,4) == 4);

    REQUIRE(fov->get_fov(2,0) == 2);
    REQUIRE(fov->get_fov(2,1) == 2);
    REQUIRE(fov->get_fov(2,2) == 2);
    REQUIRE(fov->get_fov(2,3) == 3);
    REQUIRE(fov->get_fov(2,4) == 4);

    REQUIRE(fov->get_fov(3,0) == 3);
    REQUIRE(fov->get_fov(3,1) == 3);
    REQUIRE(fov->get_fov(3,2) == 3);
    REQUIRE(fov->get_fov(3,3) == UINT_MAX);
    REQUIRE(fov->get_fov(3,4) == 5);

    REQUIRE(fov->get_fov(4,0) == 4);
    REQUIRE(fov->get_fov(4,1) == 4);
    REQUIRE(fov->get_fov(4,2) == 4);
    REQUIRE(fov->get_fov(4,3) == 5);
    REQUIRE(fov->get_fov(4,4) == UINT_MAX);
}

TEST_CASE("originalShadowCast_withFarPillarOnOblique_shouldShowSome", "[fov]")
{
    // .....
    // @....
    // ..#..
    // ....S
    // .....

    // 11234
    // 01234
    // 11234
    // 2223X
    // 33345

 
    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/5,/*width*/5);
    map->set_opaque(2, 2, true);
    std::shared_ptr<iFov> fov = 
        std::make_shared<FovTestCallback>(map->height(), map->width());


    // act
    Fov::do_fov(fov, map, /*row*/1, /*cell*/0);

    // assert
    REQUIRE(fov->get_fov(0,0) == 1);
    REQUIRE(fov->get_fov(0,1) == 1);
    REQUIRE(fov->get_fov(0,2) == 2);
    REQUIRE(fov->get_fov(0,3) == 3);
    REQUIRE(fov->get_fov(0,4) == 4);

    REQUIRE(fov->get_fov(1,0) == 0);
    REQUIRE(fov->get_fov(1,1) == 1);
    REQUIRE(fov->get_fov(1,2) == 2);
    REQUIRE(fov->get_fov(1,3) == 3);
    REQUIRE(fov->get_fov(1,4) == 4);

    REQUIRE(fov->get_fov(2,0) == 1);
    REQUIRE(fov->get_fov(2,1) == 1);
    REQUIRE(fov->get_fov(2,2) == 2);
    REQUIRE(fov->get_fov(2,3) == 3);
    REQUIRE(fov->get_fov(2,4) == 4);

    REQUIRE(fov->get_fov(3,0) == 2);
    REQUIRE(fov->get_fov(3,1) == 2);
    REQUIRE(fov->get_fov(3,2) == 2);
    REQUIRE(fov->get_fov(3,3) == 3);
    REQUIRE(fov->get_fov(3,4) == UINT_MAX);

    REQUIRE(fov->get_fov(4,0) == 3);
    REQUIRE(fov->get_fov(4,1) == 3);
    REQUIRE(fov->get_fov(4,2) == 3);
    REQUIRE(fov->get_fov(4,3) == 4);
    REQUIRE(fov->get_fov(4,4) == 5);
}

TEST_CASE("originalShadowCast_withFarPillarOnOrthogonal_shouldShowSome", "[fov]")
{
    // .....
    // .....
    // @.#SS
    // .....
    // .....

    // 22234
    // 11234
    // 012XX
    // 11234
    // 22234

    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/5,/*width*/5);
    map->set_opaque(2, 2, true);
    std::shared_ptr<iFov> fov = 
        std::make_shared<FovTestCallback>(map->height(), map->width());

    // act
    Fov::do_fov(fov, map, /*row*/2, /*cell*/0);

    // assert
    REQUIRE(fov->get_fov(0,0) == 2);
    REQUIRE(fov->get_fov(0,1) == 2);
    REQUIRE(fov->get_fov(0,2) == 2);
    REQUIRE(fov->get_fov(0,3) == 3);
    REQUIRE(fov->get_fov(0,4) == 4);

    REQUIRE(fov->get_fov(1,0) == 1);
    REQUIRE(fov->get_fov(1,1) == 1);
    REQUIRE(fov->get_fov(1,2) == 2);
    REQUIRE(fov->get_fov(1,3) == 3);
    REQUIRE(fov->get_fov(1,4) == 4);

    REQUIRE(fov->get_fov(2,0) == 0);
    REQUIRE(fov->get_fov(2,1) == 1);
    REQUIRE(fov->get_fov(2,2) == 2);
    REQUIRE(fov->get_fov(2,3) == UINT_MAX);
    REQUIRE(fov->get_fov(2,4) == UINT_MAX);

    REQUIRE(fov->get_fov(3,0) == 1);
    REQUIRE(fov->get_fov(3,1) == 1);
    REQUIRE(fov->get_fov(3,2) == 2);
    REQUIRE(fov->get_fov(3,3) == 3);
    REQUIRE(fov->get_fov(3,4) == 4);

    REQUIRE(fov->get_fov(4,0) == 2);
    REQUIRE(fov->get_fov(4,1) == 2);
    REQUIRE(fov->get_fov(4,2) == 2);
    REQUIRE(fov->get_fov(4,3) == 3);
    REQUIRE(fov->get_fov(4,4) == 4);
}

TEST_CASE("originalShadowCast_withClosePillarOnDiagonal_shouldShowSome", "[fov]")
{
    // @..
    // .#.
    // ..S

    // 012
    // 112
    // 22X

    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/3,/*width*/3);
    map->set_opaque(1, 1, true);
    std::shared_ptr<iFov> fov = 
        std::make_shared<FovTestCallback>(map->height(), map->width());


    // act
    Fov::do_fov(fov, map, /*row*/0, /*cell*/0);

    // assert
    REQUIRE(fov->get_fov(0,0) == 0);
    REQUIRE(fov->get_fov(0,1) == 1);
    REQUIRE(fov->get_fov(0,2) == 2);

    REQUIRE(fov->get_fov(1,0) == 1);
    REQUIRE(fov->get_fov(1,1) == 1);
    REQUIRE(fov->get_fov(1,2) == 2);

    REQUIRE(fov->get_fov(2,0) == 2);
    REQUIRE(fov->get_fov(2,1) == 2);
    REQUIRE(fov->get_fov(2,2) == UINT_MAX);
}

TEST_CASE("originalShadowCast_withClosePillarOnOrthogonal_shouldShowSome", "[fov]")
{
    // ...S
    // @#SS
    // ...S

    // 112X
    // 01XX
    // 112X

    // arrange
    std::shared_ptr<iWallMap> map = std::make_shared<iWallMapMock>(/*height*/3,/*width*/4);
    map->set_opaque(1, 1, true);
    std::shared_ptr<iFov> fov = 
        std::make_shared<FovTestCallback>(map->height(), map->width());

    // act
    Fov::do_fov(fov, map, /*row*/1, /*cell*/0);

    // assert
    REQUIRE(fov->get_fov(0,0) == 1);
    REQUIRE(fov->get_fov(0,1) == 1);
    REQUIRE(fov->get_fov(0,2) == 2);
    REQUIRE(fov->get_fov(0,3) == UINT_MAX);

    REQUIRE(fov->get_fov(1,0) == 0);
    REQUIRE(fov->get_fov(1,1) == 1);
    REQUIRE(fov->get_fov(1,2) == UINT_MAX);
    REQUIRE(fov->get_fov(1,3) == UINT_MAX);

    REQUIRE(fov->get_fov(2,0) == 1);
    REQUIRE(fov->get_fov(2,1) == 1);
    REQUIRE(fov->get_fov(2,2) == 2);
    REQUIRE(fov->get_fov(2,3) == UINT_MAX);
}