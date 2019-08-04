#ifndef _icurses_h_
#define _icurses_h_

//
// A c++ interface for talking to ncurses
//
class iCurses
{
public:
    // initialize the ncurses library
    virtual void* initscr() = 0;

    // closes the ncurses library
    virtual int endwin() = 0;

    // supress keyboard echo
    virtual int noecho() = 0;

    // pass keys directly to the program (without buffering)
    // convert ctrl-z, interrupt, and ctlr-c into signals
    virtual int cbreak() = 0;

    // enable reading F1-F12 and arrow keys as single keys
    virtual int keypad(void* screen, bool enable_extended_single_value) = 0;

    // clear the screen
    virtual int clear() = 0;

    // set the cursor visibility:
    // 0 - invisible
    // 1 - normal
    // 2 - very visible
    virtual int curs_set(int visibility) = 0;

    // fetch the screen size
    virtual void getmaxyx_m(void* window, int& y, int& x) = 0;

    // does this device support colors
    virtual bool has_colors() = 0;

    // enable colors
    virtual int start_color() = 0;

    // initialize a color pair
    virtual int init_pair(short index, short foreground, short background) = 0;

    // turn on an attribute (used for color pairs)
    virtual int attron_m(int attributes) = 0;

    // turn off an attribute (used for color pairs)
    virtual int attroff_m(int attributes) = 0;

    // add a character to specific spot in a window
    virtual int mvwaddch_m(void* window, int y, int x, unsigned long ch) = 0;

    // get keyboard input
    virtual int getch_m() = 0;

    // write a message to the window
    virtual int printw(const char * message) = 0;

    // create a new topmost window
    virtual void* newwin(int nlines, int ncols, int begin_y, int begin_x) = 0;

    // destroy a window
    virtual int delwin(void* window) = 0;

    // redraw a window
    virtual int wrefresh(void* window) = 0;

    // fetch the standard screen
    virtual void* stdscr_m() = 0;

    // fetch the up key
    virtual int key_up() = 0;

    // fetch the up+right key
    virtual int key_up_right() = 0;

    // fetch the right key
    virtual int key_right() = 0;

    // fetch the down+right key
    virtual int key_down_right() = 0;

    // fetch the down key
    virtual int key_down() = 0;

    // fetch the down+left key
    virtual int key_down_left() = 0;

    // fetch the left key
    virtual int key_left() = 0;

    // fetch the left+up key
    virtual int key_up_left() = 0;
};

#endif // _icurses_h_