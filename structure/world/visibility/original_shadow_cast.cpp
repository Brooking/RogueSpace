#include <cmath>
#include "original_shadow_cast.h"

static int multipliers[4][8] = {
    {1, 0, 0, -1, -1, 0, 0, 1},
    {0, 1, -1, 0, 0, -1, 1, 0},
    {0, 1, 1, 0, 0, -1, -1, 0},
    {1, 0, 0, 1, -1, 0, 0, -1}
};

void cast_light(iMap& map, uint x, uint y, uint radius, uint row,
        float start_slope, float end_slope, uint xx, uint xy, uint yx,
        uint yy) {
    if (start_slope < end_slope) {
        return;
    }
    float next_start_slope = start_slope;
    for (uint i = row; i <= radius; i++) {
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
            if ((sax < 0 && (uint)std::abs(sax) > x) ||
                    (say < 0 && (uint)std::abs(say) > y)) {
                continue;
            }
            uint ax = x + sax;
            uint ay = y + say;
            if (ax >= map.get_width() || ay >= map.get_height()) {
                continue;
            }

            uint radius2 = radius * radius;
            if ((uint)(dx * dx + dy * dy) < radius2) {
                // save the square of the distance
                map.set_los(ax, ay, dx * dx + dy * dy);
            }

            if (blocked) {
                if (map.is_opaque(ax, ay)) {
                    next_start_slope = r_slope;
                    continue;
                } else {
                    blocked = false;
                    start_slope = next_start_slope;
                }
            } else if (map.is_opaque(ax, ay)) {
                blocked = true;
                next_start_slope = r_slope;
                cast_light(map, x, y, radius, i + 1, start_slope, l_slope, xx,
                        xy, yx, yy);
            }
        }
        if (blocked) {
            break;
        }
    }
}

void do_fov(iMap& map, uint x, uint y)
{
    // slightly larger than the actual maximum (diagonal)
    int longest_dist = map.get_height() + map.get_width(); 
    do_fov(map, x, y, longest_dist);    
}

void do_fov(iMap& map, uint x, uint y, uint radius) {

    map.set_los(x, y, 0);
    if (radius == 0)
    {
        radius = std::max(map.get_height(), map.get_width());
    }

    for (uint i = 0; i < 8; i++) {
        cast_light(map, x, y, radius, 1, 1.0, 0.0, multipliers[0][i],
                multipliers[1][i], multipliers[2][i], multipliers[3][i]);
    }
}