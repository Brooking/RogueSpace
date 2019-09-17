#ifndef _fov_h_
#define _fov_h_

#include "../ifov.h"
#include "../iwall_map.h"

//
// calculate a field of view, using the shadow casting algorithm
//

// calculate for the entire map
void do_fov(
    std::shared_ptr<iFov>& fov_response,
    std::shared_ptr<iWallMap>& wall_map,
    uint row,
    uint cell);

// calculate only for a given radius around the origin
void do_fov(
    std::shared_ptr<iFov>& fov_response,
    std::shared_ptr<iWallMap>& wall_map,
    uint row,
    uint cell,
    uint radius);

#endif // _fov_h_