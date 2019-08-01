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
    void Add(const char* Message);

    // accessors
    int Width();
    int Height();

private:
    iCurses& curses_;
    int _width;
    int _height;
};

#endif // screen_h_