#include <ncurses.h>
#include <assert.h>
#include "rawcurses.h"

RawCurses::RawCurses()
{
    RawCurses::validate_statics();
}

void* RawCurses::initscr()
{
    return ::initscr();
}

int RawCurses::endwin()
{
    return ::endwin();
}

int RawCurses::noecho()
{
    return ::noecho();
}

int RawCurses::cbreak()
{
    return ::cbreak();
}

int RawCurses::keypad(void* screen, bool enable_extended_single_value)
{
    return ::keypad((WINDOW*)screen, enable_extended_single_value);
}

int RawCurses::clear()
{
    return ::clear();
}

int RawCurses::curs_set(int visibility)
{
    return ::curs_set(visibility);
}

void RawCurses::getmaxyx_m(void* window, int& y, int& x)
{
    // call the macro
    getmaxyx((WINDOW*)window, y, x);
}

bool RawCurses::has_colors()
{
    return ::has_colors();
}

int RawCurses::start_color()
{
    return ::start_color();
}

int RawCurses::init_pair(short index, short foreground, short background)
{
    return ::init_pair(index, foreground, background);
}

int RawCurses::attron_m(int attributes)
{
    // call the macro
    return attron(attributes);
}

int RawCurses::attroff_m(int attributes)
{
    // call the macro
    return attroff(attributes);
}

int RawCurses::mvwaddch_m(void* window, int y, int x, unsigned long ch)
{
    // call the macro
    return mvwaddch((WINDOW*)window, y, x, ch);
}

int RawCurses::getch_m()
{
    return getch();
}

int RawCurses::printw(const char * message)
{
    return ::printw(message);
}

void* RawCurses::newwin(int nlines, int ncols, int begin_y, int begin_x)
{
    return (void*)::newwin(nlines, ncols, begin_y, begin_x);
}

int RawCurses::delwin(void* window)
{
    return ::delwin((WINDOW*)window);
}

int RawCurses::wrefresh(void* window)
{
    return ::wrefresh((WINDOW*)window);
}

void* RawCurses::stdscr_m()
{
    return ::stdscr;
}

// initialize static variables
void RawCurses::validate_statics()
{
    // in order for the curses macros to be correct, we must call the curses initializer
    // but the class does not yet exist, so use the raw one
    ::initscr();    

    // set our local key statics
    assert(RawCurses::UP == KEY_UP);
    assert(RawCurses::UP_RIGHT == KEY_PPAGE);
    assert(RawCurses::RIGHT == KEY_RIGHT);
    assert(RawCurses::DOWN_RIGHT == KEY_NPAGE);
    assert(RawCurses::DOWN == KEY_DOWN);
    assert(RawCurses::DOWN_LEFT == KEY_END);
    assert(RawCurses::LEFT == KEY_LEFT);
    assert(RawCurses::UP_LEFT == KEY_HOME);

    // set our local character statics
    assert(RawCurses::WALL_NS == ACS_VLINE);
    assert(RawCurses::WALL_EW == ACS_HLINE);
    assert(RawCurses::WALL_NE == ACS_LLCORNER);
    assert(RawCurses::WALL_SE == ACS_ULCORNER);
    assert(RawCurses::WALL_SW == ACS_URCORNER);
    assert(RawCurses::WALL_NW == ACS_LRCORNER);
    assert(RawCurses::WALL_NSE == ACS_LTEE);
    assert(RawCurses::WALL_NSW == ACS_RTEE);
    assert(RawCurses::WALL_NEW == ACS_BTEE);
    assert(RawCurses::WALL_SEW == ACS_TTEE);
    assert(RawCurses::WALL_NSEW == ACS_PLUS);

    assert(RawCurses::BULLET == ACS_BULLET);


    ::endwin();
};

// static storage (note these are copied from ncurses)
const unsigned long RawCurses::UP = 259;
const unsigned long RawCurses::UP_RIGHT = 339;
const unsigned long RawCurses::RIGHT = 261;
const unsigned long RawCurses::DOWN_RIGHT = 338;
const unsigned long RawCurses::DOWN = 258;
const unsigned long RawCurses::DOWN_LEFT = 360;
const unsigned long RawCurses::LEFT = 260;
const unsigned long RawCurses::UP_LEFT = 262;
const unsigned long RawCurses::WALL_NS = 4194424;
const unsigned long RawCurses::WALL_EW = 4194417;
const unsigned long RawCurses::WALL_NE = 4194413;
const unsigned long RawCurses::WALL_SE = 4194412;
const unsigned long RawCurses::WALL_SW = 4194411;
const unsigned long RawCurses::WALL_NW = 4194410;
const unsigned long RawCurses::WALL_NSE = 4194420;
const unsigned long RawCurses::WALL_NSW = 4194421;
const unsigned long RawCurses::WALL_NEW = 4194422;
const unsigned long RawCurses::WALL_SEW = 4194423;
const unsigned long RawCurses::WALL_NSEW = 4194414;
const unsigned long RawCurses::BULLET = 4194430;