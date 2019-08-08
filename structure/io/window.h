#ifndef _io_window_h_
#define _io_window_h_

#include "rawcurses.h"
#include "screen.h"

namespace io
{

class Window 
{
public:
    // construct a window
    Window(
        Screen& screen,
        RawCurses& curses,
        unsigned int screen_row, 
        unsigned int screen_cell, 
        unsigned int num_rows, 
        unsigned int num_cells);

    // destructor
    virtual ~Window();

    // place a colored character at the given spot in the window
    void place_character(
        unsigned int row,
        unsigned int cell,
        unsigned int character,
        unsigned int color_pair_index = 1);

    // push all changes to the actual screen
    void refresh();

private:
    Screen& screen_;
    RawCurses& curses_;
    unsigned int screen_row_;
    unsigned int screen_cell_;
    unsigned int height_;
    unsigned int width_;
    void* window_;
};

} // namespace io

#endif // _io_window_h_