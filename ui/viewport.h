#ifndef _viewport_h_
#define _viewport_h_

#include "io_constants.h"
#include "ifloor.h"
#include "ipane.h"
#include "iscreen.h"
#include "iupdate.h"
#include "iwindow.h"

//
// a pane that shows the world from above
//
class Viewport final : public iPane
{
public:
    Viewport(
        std::shared_ptr<iScreen> screen, 
        std::shared_ptr<iFloor> floor,
        unsigned int screen_row,
        unsigned int screen_cell, 
        unsigned int height,
        unsigned int width, 
        unsigned int center_row,
        unsigned int center_cell);
    ~Viewport() {
        this->screen_ = nullptr;
    }

    // iPane: get the screen
    std::shared_ptr<iScreen> screen() const override { return this->screen_; };

    // iUpdate: a sepecific update notification from the world
    bool update(unsigned int row, unsigned int cell, bool center = false) override;

    // iUpdate: a general update notification from the world
    bool update() override;

    // iPane: get the screen row
    unsigned int screen_row() const override { return this->screen_row_; }

    // iPane: get the screen cell
    unsigned int screen_cell() const override { return this->screen_cell_; }

    // iPane: get the pane height
    unsigned int height() const override { return this->height_; }

    // iPane: get the pane width
    unsigned int width() const override { return this->width_; }

    // iPane: completely refill the pane (includes a full update)
    void refill() override;

    // iPane: time to implement all of the updates (normally called from the game)
    void refresh();

private:
    // update a given spot in the window
    bool update_worker(unsigned int row, unsigned int cell);

    // update the center (and if it moves update the whole window)
    bool update_center(unsigned int center_row, unsigned int center_cell, bool update);

private:
    std::shared_ptr<iScreen> screen_;
    std::shared_ptr<iWindow> window_;
    std::shared_ptr<iFloor> floor_;

    unsigned int screen_row_;
    unsigned int screen_cell_;
    unsigned int height_;
    unsigned int width_;
    int window_origin_row_offset_from_floor_;
    int window_origin_cell_offset_from_floor_;
};

#endif // _viewport_h_