#ifndef _ipane_h_
#define _ipane_h_

#include "../inc/iupdate.h"
#include "io/screen.h"

//
// interface to a single pane
//
class iPane : public iUpdate
{
public:
    virtual ~iPane() {}

    // get the screen
    virtual std::shared_ptr<io::Screen> screen() const = 0;

    // get the screen row
    virtual unsigned int screen_row() const = 0;

    // get the screen cell
    virtual unsigned int screen_cell() const = 0;

    // get the pane height
    virtual unsigned int height() const = 0;

    // get the pane width
    virtual unsigned int width() const = 0;

    // completely refill the pane (includes a full update)
    virtual void refill() = 0;

    // tell the pane to refresh (actually display changes to the screen)
    // (usually the main game UI will call this)
    virtual void refresh() = 0;

    // nonvirtual helper for pane locations
    bool is_colocated_with(std::shared_ptr<iPane> that)
    {
        return 
            this->screen_row() == that->screen_row() &&
            this->screen_cell() == that->screen_cell() &&
            this->height() == that->height() &&
            this->width() == that->width();
    }
};

#endif // _ipane_h_