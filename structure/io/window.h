#ifndef _io_window_h_
#define _io_window_h_

#include "icurses.h"
#include "screen.h"

namespace io
{

class Window
{
public:
    // construct a window
    Window(
        std::shared_ptr<Screen> screen,
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
        io::Color foreground,
        io::Color background);

    // push all changes to the actual screen
    void refresh();

private:
    std::shared_ptr<Screen> screen_;
    unsigned int screen_row_;
    unsigned int screen_cell_;
    unsigned int height_;
    unsigned int width_;
    void* curses_window_;
};

} // namespace io

#endif // _io_window_h_