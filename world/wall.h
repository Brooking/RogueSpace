#ifndef _wall_h_
#define _wall_h_

#include <array>
#include <stdexcept>
#include "thing_base.h"
#include "tile.h"
#include "floor.h"
#include "uitoken.h"

//
// Adjacency information (used in drawing walls)
//
enum class AdjacentWallBits
{
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

//
// Adjacency deltas (used in drawing walls)
//
static const std::array<std::pair<int,int>, 4> AdjacencyDelta
{
    /* North  */std::pair<int,int>(-1,0),
    /* East   */std::pair<int,int>(0,+1),
    /* South  */std::pair<int,int>(+1,0),
    /* West   */std::pair<int,int>(0,-1)
};

//
// Table giving wall shapes based on wall adjacencies
// todo not really needed - the values of WallType == index in this list...
//
static const std::array<WallType,16> AdjacentWallList
{
    /* 0:NONE*/WallType::pillar,
    /* 1:N   */WallType::n,
    /* 2:E   */WallType::e,
    /* 3:NE  */WallType::ne,
    /* 4:S   */WallType::s,
    /* 5:NS  */WallType::ns,
    /* 6:SE  */WallType::se,
    /* 7:NSE */WallType::nse,
    /* 8:W   */WallType::w,
    /* 9:NW  */WallType::nw,
    /*10:EW  */WallType::we,
    /*11:NEW */WallType::nwe,
    /*12:SW  */WallType::sw,
    /*13:NSW */WallType::nsw,
    /*14:SEW */WallType::swe,
    /*15:NSEW*/WallType::nswe
};

class Wall : public ThingBase
{
public:
    Wall() : 
        ThingBase(TokenType::wall, ContentSize::full, /*center*/false)
    {}

    virtual ~Wall() = default;

    // iThing: return the ui token
    virtual UIToken token() const override
    {
        std::shared_ptr<Tile> tile = this->tile();
        std::shared_ptr<Floor> floor = tile->floor();
        if (floor == nullptr)
        {
            return UIToken(WallType::pillar);
        }
        int floor_row = tile->where().row();
        int floor_cell = tile->where().cell();

        std::bitset<8> adjacency;
        for (unsigned int i = 0; i < AdjacencyDelta.size(); i++)
        {
            std::shared_ptr<Tile> adjacent_tile = floor->tile(
                Location(
                    floor_row + AdjacencyDelta[i].first, 
                    floor_cell + AdjacencyDelta[i].second));
            if (adjacent_tile != nullptr)
            {
                adjacency[i] = (adjacent_tile->is_wall());
            }
        }
        WallType wall_type = AdjacentWallList[static_cast<int>(adjacency.to_ulong())];

        return UIToken(
            wall_type, 
            tile->hero_can_see(), 
            tile->has_been_seen(), 
            tile->is_lit());
    }
};

#endif // _wall.h_