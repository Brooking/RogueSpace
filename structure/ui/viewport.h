#ifndef _viewport_h_
#define _viewport_h_

#include "io_constants.h"
#include "ifloor.h"
#include "iupdate.h"
#include "screen.h"
#include "window.h"

//
// a pane that shows the world from above
//
class Viewport : public iUpdate
{
public:
    Viewport(
        std::shared_ptr<io::Screen> screen, 
        std::shared_ptr<iFloor> floor, 
        unsigned int height,
        unsigned int width, 
        int center_row,
        int center_cell);
    virtual ~Viewport() {
        this->screen_ = nullptr;
    }

    // iUpdate: an update notification from the world
    virtual bool update(int row, int cell, bool center = false) override;

    // time to implement all of the updates (normally called from the game)
    void refresh();

    // get this viewport's parent screen
    std::shared_ptr<io::Screen> screen() { return this->screen_; }

private:
    // update all spots in the window
    bool full_update();

    // update a given spot in the window
    bool update_worker(unsigned int row, unsigned int cell);

    // update the center (and if it moves update the whole window)
    bool update_center(int center_row, int center_cell);  

private:
    std::shared_ptr<io::Screen> screen_;
    io::Window* window_;
    std::shared_ptr<iFloor> floor_;

    unsigned int height_;
    unsigned int width_;
    int window_origin_row_offset_from_floor_;
    int window_origin_cell_offset_from_floor_;
};

#endif // _viewport_h_