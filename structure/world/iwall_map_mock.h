#ifndef _iwall_map_mock_h_
#define _iwall_map_mock_h_

#include "iwall_map.h"

//
// a mock of iWallMap
//
class iWallMapMock : public iWallMap
{
public:
    iWallMapMock(uint height, uint width) :
        wall_map_(std::vector<std::vector<bool>>(height, std::vector<bool>(width, false)))
    {}
    virtual ~iWallMapMock() = default;

    // iMap: Return the width of the map.
    uint width() const override { return static_cast<uint>(this->wall_map_[0].size()); }

    // iMap: Return the height of the map.
    uint height() const override { return static_cast<uint>(this->wall_map_.size()); }

    // iMap: Is there a wall in this spot
    bool is_opaque(uint row, uint cell) const override
    {
        return this->wall_map_[row][cell];
    }

    // iMap: Set a wall.
    void set_opaque(uint row, uint cell, bool is_opaque) override
    {
        this->wall_map_[row][cell] = is_opaque;
    }

private:
    std::vector<std::vector<bool>> wall_map_;   
};

#endif // _iwall_map_mock_h_