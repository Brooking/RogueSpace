#ifndef _realcurses_h_
#define _realcurses_h_

#include "icurses.h"

//
// A class to wrap the actual ncurses implementation
//
class Curses : public iCurses
{
public:
    Curses() {}
    virtual ~Curses() {}

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
    virtual int mvwaddch_m(void* window, int y, int x, char ch);
    virtual int getch_m();
    virtual int printw(const char * message);
    virtual void* newwin(int nlines, int ncols, int begin_y, int begin_x);
    virtual void* derwin(void* orig, int nlines, int ncols, int begin_y, int begin_x);
    virtual int delwin(void* window);
    virtual int mvderwin(void* window, int y, int x);    
    virtual void* stdscr_m();
};

#endif // _realcurses_h_