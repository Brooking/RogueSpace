#ifndef _fov_h_
#define _fov_h_

#include "../ifov.h"
#include "../iwall_map.h"

//
// calculate a field of view, using the shadow casting algorithm
//

class Fov
{
public:
    // calculate for the entire map
    static void do_fov(
        std::shared_ptr<iFov>& fov_response,
        std::shared_ptr<iWallMap>& wall_map,
        uint row,
        uint cell);

    // calculate only for a given radius around the origin
    static void do_fov(
        std::shared_ptr<iFov>& fov_response,
        std::shared_ptr<iWallMap>& wall_map,
        uint row,
        uint cell,
        uint radius);

private:
    static const int Multipliers[4][8];

    static void cast_light(std::shared_ptr<iFov>& fov_response,
            std::shared_ptr<iWallMap>& map,
            uint row, uint cell, uint radius, uint row_start,
            float start_slope, float end_slope, uint xx, uint xy, uint yx,
            uint yy);

};
#endif // _fov_h_