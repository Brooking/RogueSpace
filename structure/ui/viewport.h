#ifndef _viewport_h_
#define _viewport_h_

#include "icurses.h"
#include "screen.h"
#include "ifloor.h"
#include "location.h"
#include "iupdate.h"

//
// a pane that shows the world from above
//
class Viewport : public iUpdate
{
public:
    Viewport(iCurses& curses, iFloor& floor, unsigned int height, unsigned int width, Location center);
    virtual ~Viewport() {}

    // iUpdate: an update notification from the world
    virtual bool update(Location location, bool center = false);

    // time to implement all of the updates (normally called from the game)
    bool refresh();

private:
    // update all spots in the window
    bool full_update();

    // update a given spot in the window
    bool update(unsigned int row, unsigned int cell);

    // update the center (and if it moves update the whole window)
    bool update_center(Location center);  

private:
    iCurses& curses_;
    iFloor& floor_;

    unsigned int height_;
    unsigned int width_;
    int window_origin_row_offset_from_floor_;
    int window_origin_cell_offset_from_floor_;
    void* window_;
};

#endif // _viewport_h_