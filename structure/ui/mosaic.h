#ifndef _mosaic_h_
#define _mosaic_h_

#include <memory>
#include <vector>
#include "ipane.h"
#include "../inc/iupdate.h"
#include "io/screen.h"

//
// The 'window' that holds all of the panes
//
// The mosaic must always be filled in with panes that touch existing panes (or edges) on three
// sides. That way there is (at most) a single blank pane in the center. And while it is getting
// filled the empty space left is always a rectangle.
// 
class Mosaic : public iPane
{
public:
    Mosaic(std::shared_ptr<io::Screen> screen);

    // iPane: get the screen
    std::shared_ptr<io::Screen> screen() const override { return this->screen_; };

    // iUpdate: update the mosaic for a single spot
    bool update(unsigned int row, unsigned int cell, bool center = false) override;

    // iPane: update the whole mosaic
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
    void refresh() override;

    // add a pane to the base of the mosaic
    bool add(std::shared_ptr<iPane> pane);

    // remove a pane from the mosaic
    bool remove(std::shared_ptr<iPane> pane);

    // add a pane exactly over an existing pane in the mosaic
    bool overlay(std::shared_ptr<iPane> pane);

private:
    std::shared_ptr<io::Screen> screen_;
    std::vector<std::shared_ptr<iPane>> panes_;
    std::shared_ptr<iPane> blank_pane_;
    std::vector<std::shared_ptr<iPane>> covered_panes_;

    unsigned int screen_row_;
    unsigned int screen_cell_;
    unsigned int height_;
    unsigned int width_;
};

#endif // _mosaic_h_