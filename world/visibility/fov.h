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
        std::shared_ptr<iFov> &fov_response,
        std::shared_ptr<iWallMap> &wall_map,
        unsigned int row,
        unsigned int cell);

    // calculate only for a given radius around the origin
    static void do_fov(
        std::shared_ptr<iFov> &fov_response,
        std::shared_ptr<iWallMap> &wall_map,
        unsigned int row,
        unsigned int cell,
        unsigned int radius);

private:
    static const int Multipliers[4][8];

    static void cast_light(
        std::shared_ptr<iFov> &fov_response,
        std::shared_ptr<iWallMap> &map,
        unsigned int row,
        unsigned int cell,
        unsigned int radius,
        unsigned int row_start,
        float start_slope,
        float end_slope,
        int xx,
        int xy,
        int yx,
        int yy);
};
#endif // _fov_h_