#include <algorithm>
#include <cmath>
#include <memory>
#include "fov.h"

const int Fov::Multipliers[4][8] = {
    {1, 0, 0, -1, -1, 0, 0, 1},
    {0, 1, -1, 0, 0, -1, 1, 0},
    {0, 1, 1, 0, 0, -1, -1, 0},
    {1, 0, 0, 1, -1, 0, 0, -1}
};

void Fov::cast_light(
    std::shared_ptr<iFov>& fov_response,
    std::shared_ptr<iWallMap>& map,
    unsigned int row,
    unsigned int cell,
    unsigned int radius,
    unsigned int row_start,
    float start_slope,
    float end_slope,
    int xx,
    int xy,
    int yx,
    int yy)
{
    if (start_slope < end_slope)
    {
        return;
    }
    float next_start_slope = start_slope;
    for (unsigned int i = row_start; i <= radius; i++)
    {
        bool blocked = false;
        for (int dx = -(int)i, dy = -(int)i; dx <= 0; dx++)
        {
            float l_slope = static_cast<float>((dx - 0.5) / (dy + 0.5));
            float r_slope = static_cast<float>((dx + 0.5) / (dy - 0.5));
            if (start_slope < r_slope)
            {
                continue;
            }
            else if (end_slope > l_slope)
            {
                break;
            }

            int sax = dx * xx + dy * xy;
            int say = dx * yx + dy * yy;
            if ((sax < 0 && (unsigned int)std::abs(sax) > cell) ||
                (say < 0 && (unsigned int)std::abs(say) > row))
            {
                continue;
            }
            unsigned int ax = cell + (unsigned int)sax;
            unsigned int ay = row + (unsigned int)say;
            if (ax >= map->width() || ay >= map->height())
            {
                continue;
            }

            unsigned int radius2 = radius * radius;
            if ((unsigned int)(dx * dx + dy * dy) < radius2)
            {
                // todo: save the square of the distance
                fov_response->set_fov(ay, ax, static_cast<unsigned int>(sqrt(dx * dx + dy * dy)));
            }

            if (blocked)
            {
                if (map->is_opaque(ay, ax))
                {
                    next_start_slope = r_slope;
                    continue;
                }
                else
                {
                    blocked = false;
                    start_slope = next_start_slope;
                }
            }
            else if (map->is_opaque(ay, ax))
            {
                blocked = true;
                next_start_slope = r_slope;
                cast_light(
                    fov_response,
                    map, 
                    row,
                    cell,
                    radius,
                    /*row_start*/i + 1, 
                    start_slope,
                    l_slope,
                    xx,
                    xy,
                    yx,
                    yy);
            }
        }

        if (blocked)
        {
            break;
        }
    }
}

void Fov::do_fov(
    std::shared_ptr<iFov>& fov_response,
    std::shared_ptr<iWallMap>& map,
    unsigned int row,
    unsigned int cell)
{
    // slightly larger than the actual maximum (diagonal)
    unsigned int longest_dist = map->height() + map->width(); 
    Fov::do_fov(fov_response, map, row, cell, longest_dist);    
}

void Fov::do_fov(
    std::shared_ptr<iFov>& fov_response,
    std::shared_ptr<iWallMap>& map,
    unsigned int row,
    unsigned int cell,
    unsigned int radius)
{
    fov_response->set_fov(row, cell, 0);
    if (radius == 0)
    {
        radius = std::max(map->height(), map->width());
    }

    for (unsigned int i = 0; i < 8; i++)
    {
        cast_light(
            fov_response,
            map,
            row,
            cell,
            radius,
            /*row_start*/1,
            /*start_slope*/1.0,
            /*end_slope*/0.0, 
            Multipliers[0][i],
            Multipliers[1][i],
            Multipliers[2][i],
            Multipliers[3][i]);
    }
}