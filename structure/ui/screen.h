#ifndef _screen_h_
#define _screen_h_

#include "icurses.h"

class Screen {
public:
    // Initialize the screen
    Screen(iCurses& curses);

    // tear down the screen
    ~Screen();

    // Print a message to the screen
    void add(const char* Message);

    // accessors
    int width();
    int height();

private:
    iCurses& curses_;
    int width_;
    int height_;
};

#endif // screen_h_