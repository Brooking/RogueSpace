#ifndef _rawcurses_h_
#define _rawcurses_h_

#include "icurses.h"

//
// A class to wrap the actual ncurses implementation
//
class RawCurses : public iCurses
{
public:
    RawCurses();
    virtual ~RawCurses() {}

    virtual void* initscr();
    virtual int endwin();
    virtual int noecho();
    virtual int cbreak();
    virtual int keypad(void* window, bool enable_extended_single_value);
    virtual int clear();
    virtual int curs_set(int visibility);
    virtual void getmaxyx_m(void* screen, int& y, int& x);
    virtual bool has_colors();
    virtual int start_color();
    virtual int init_pair(short index, short foreground, short background);
    virtual int attron_m(int attributes);
    virtual int attroff_m(int attributes);
    virtual int mvwaddch_m(void* window, int y, int x, unsigned long ch);
    virtual int getch_m();
    virtual int printw(const char * message);
    virtual void* newwin(int nlines, int ncols, int begin_y, int begin_x);
    virtual int delwin(void* window);
    virtual int wrefresh(void* window);
    virtual void* stdscr_m();
    virtual int key_up();
    virtual int key_up_right();
    virtual int key_right();
    virtual int key_down_right();
    virtual int key_down();
    virtual int key_down_left();
    virtual int key_left();
    virtual int key_up_left();

/*static:*/

    // keys
    static int UP;
    static int UP_RIGHT;
    static int RIGHT;
    static int DOWN_RIGHT;
    static int DOWN;
    static int DOWN_LEFT;
    static int LEFT;
    static int UP_LEFT;

    // special characters
    static int WALL_NS;
    static int WALL_EW;
    static int WALL_NE;
    static int WALL_SE;
    static int WALL_SW;
    static int WALL_NW;
    static int WALL_NSE;
    static int WALL_NSW;
    static int WALL_NEW;
    static int WALL_SEW;
    static int WALL_NSEW;

private:
    static void static_initialize();
    static bool initialized;
};

#endif // _rawcurses_h_