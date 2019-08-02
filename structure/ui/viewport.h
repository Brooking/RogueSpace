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
    Viewport(iCurses& curses, Screen& screen, iFloor& floor, Location center);
    virtual ~Viewport() {}

    bool full_update();
    bool update_center(Location center);
    
    bool update(Location location);
    bool refresh();

private:
    iCurses& curses_;
    Screen& screen_;
    iFloor& floor_;
    Location anchor_;
    void* parent_window_;
    void* child_window_;
};

#endif // _viewport_h_