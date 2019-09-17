#include <cmath>
#include "fov.h"

static int multipliers[4][8] = {
    {1, 0, 0, -1, -1, 0, 0, 1},
    {0, 1, -1, 0, 0, -1, 1, 0},
    {0, 1, 1, 0, 0, -1, -1, 0},
    {1, 0, 0, 1, -1, 0, 0, -1}
};

void cast_light(std::shared_ptr<iFov>& fov_response,
        std::shared_ptr<iWallMap>& map,
        uint row, uint cell, uint radius, uint row_start,
        float start_slope, float end_slope, uint xx, uint xy, uint yx,
        uint yy) {
    if (start_slope < end_slope) {
        return;
    }
    float next_start_slope = start_slope;
    for (uint i = row_start; i <= radius; i++) {
        bool blocked = false;
        for (int dx = -i, dy = -i; dx <= 0; dx++) {
            float l_slope = static_cast<float>((dx - 0.5) / (dy + 0.5));
            float r_slope = static_cast<float>((dx + 0.5) / (dy - 0.5));
            if (start_slope < r_slope) {
                continue;
            } else if (end_slope > l_slope) {
                break;
            }

            int sax = dx * xx + dy * xy;
            int say = dx * yx + dy * yy;
            if ((sax < 0 && (uint)std::abs(sax) > cell) ||
                (say < 0 && (uint)std::abs(say) > row)) {
                continue;
            }
            uint ax = cell + sax;
            uint ay = row + say;
            if (ax >= map->width() || ay >= map->height()) {
                continue;
            }

            uint radius2 = radius * radius;
            if ((uint)(dx * dx + dy * dy) < radius2) {
                // todo: save the square of the distance
                fov_response->set_fov(ay, ax, static_cast<unsigned int>(sqrt(dx * dx + dy * dy)));
            }

            if (blocked) {
                if (map->is_opaque(ay, ax)) {
                    next_start_slope = r_slope;
                    continue;
                } else {
                    blocked = false;
                    start_slope = next_start_slope;
                }
            } else if (map->is_opaque(ay, ax)) {
                blocked = true;
                next_start_slope = r_slope;
                cast_light(fov_response, map, row, cell, radius, i + 1, start_slope, l_slope, xx,
                        xy, yx, yy);
            }
        }
        if (blocked) {
            break;
        }
    }
}

void do_fov(
    std::shared_ptr<iFov>& fov_response,
    std::shared_ptr<iWallMap>& map,
    uint row, uint cell)
{
    // slightly larger than the actual maximum (diagonal)
    int longest_dist = map->height() + map->width(); 
    do_fov(fov_response, map, row, cell, longest_dist);    
}

void do_fov(
    std::shared_ptr<iFov>& fov_response,
    std::shared_ptr<iWallMap>& map,
    uint row,
    uint cell,
    uint radius) {

    fov_response->set_fov(row, cell, 0);
    if (radius == 0)
    {
        radius = std::max(map->height(), map->width());
    }

    for (uint i = 0; i < 8; i++) {
        cast_light(fov_response, map, row, cell, radius, 1, 1.0, 0.0, multipliers[0][i],
                multipliers[1][i], multipliers[2][i], multipliers[3][i]);
    }
}