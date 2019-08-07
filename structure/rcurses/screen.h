#ifndef _rcurses_screen_h_
#define _rcurses_screen_h_

#include "constants.h"

namespace rcurses
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
    static Screen* open_screen(RawCurses& curses);

    // deleter
    static void close_screen(Screen& screen);

    // Print a message to the screen
    void add(const char* Message);

    // accessors
    int width();
    int height();

    // create a window
    Window* create_window(unsigned int screen_row, 
                          unsigned int screen_cell, 
                          unsigned int num_rows, 
                          unsigned int num_cells);

    // wait for a character
    unsigned int get_key_input();

private:
    // Initialize the screen
    Screen(RawCurses& curses);

    // tear down the screen
    ~Screen();

private:
    RawCurses& curses_;
    int width_;
    int height_;

    static int ref_count;
    static Screen* singleton;
};

} // namespace rcurses

#endif // _rcurses_screen_h_
