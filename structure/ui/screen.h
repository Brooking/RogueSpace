#ifndef _screen_h_
#define _screen_h_

namespace io
{
class RawCurses;
}

class Screen {
public:
    // Initialize the screen
    Screen(io::RawCurses& curses);

    // tear down the screen
    ~Screen();

    // Print a message to the screen
    void add(const char* Message);

    // accessors
    int width();
    int height();

private:
    io::RawCurses& curses_;
    int width_;
    int height_;
};

#endif // screen_h_