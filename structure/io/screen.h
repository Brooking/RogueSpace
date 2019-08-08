#ifndef _io_screen_h_
#define _io_screen_h_

#include "io_constants.h"

namespace io
{

class Window;
class RawCurses;

//
// A singleton representing the screen
//
class Screen
{
public:
    // creator
    static io::Screen* open_screen(io::RawCurses& curses);

    // deleter
    static void close_screen(io::Screen& screen);

    // Print a message to the screen
    void add(const char* Message);

    // accessors
    int width();
    int height();

    // create a window
    io::Window* create_window(unsigned int screen_row, 
                          unsigned int screen_cell, 
                          unsigned int num_rows, 
                          unsigned int num_cells);

    // wait for a character
    unsigned int get_key_input();

private:
    // Initialize the screen
    Screen(io::RawCurses& curses);

    // tear down the screen
    ~Screen();

private:
    io::RawCurses& curses_;
    int width_;
    int height_;

    static int ref_count;
    static io::Screen* singleton;
};

} // namespace io

#endif // _io_screen_h_
