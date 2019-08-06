#include <ncurses.h>
#include "rawcurses.h"

RawCurses::RawCurses()
{
    if (!RawCurses::initialized)
    {
        RawCurses::static_initialize();
        RawCurses::initialized = true;
    }
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

int RawCurses::keypad(void* window, bool enable_extended_single_value)
{
    return ::keypad((WINDOW*)window, enable_extended_single_value);
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

int RawCurses::key_up()
{
    return RawCurses::UP;
}

int RawCurses::key_up_right()
{
    return RawCurses::UP_RIGHT;
}

int RawCurses::key_right()
{
    return RawCurses::RIGHT;
}

int RawCurses::key_down_right()
{
    return RawCurses::DOWN_RIGHT;
}

int RawCurses::key_down()
{
    return RawCurses::DOWN;
}

int RawCurses::key_down_left()
{
    return RawCurses::DOWN_LEFT;
}

int RawCurses::key_left()
{
    return RawCurses::LEFT;
}

int RawCurses::key_up_left()
{
    return RawCurses::UP_LEFT;    
}

// initialize static variables
void RawCurses::static_initialize()
{
    // in order for the curses macros to be correct, we must call the curses initializer
    // but the class does not yet exist, so use the raw one
    ::initscr();    

    // set our local key statics
    RawCurses::UP = KEY_UP;
    RawCurses::UP_RIGHT = KEY_PPAGE;
    RawCurses::RIGHT = KEY_RIGHT;
    RawCurses::DOWN_RIGHT = KEY_NPAGE;
    RawCurses::DOWN = KEY_DOWN;
    RawCurses::DOWN_LEFT = KEY_END;
    RawCurses::LEFT = KEY_LEFT;
    RawCurses::UP_LEFT = KEY_HOME;

    // set our local character statics
    RawCurses::WALL_NS = ACS_VLINE;
    RawCurses::WALL_EW = ACS_HLINE;
    RawCurses::WALL_NE = ACS_LLCORNER;
    RawCurses::WALL_SE = ACS_ULCORNER;
    RawCurses::WALL_SW = ACS_URCORNER;
    RawCurses::WALL_NW = ACS_LRCORNER;
    RawCurses::WALL_NSE = ACS_LTEE;
    RawCurses::WALL_NSW = ACS_RTEE;
    RawCurses::WALL_NEW = ACS_BTEE;
    RawCurses::WALL_SEW = ACS_TTEE;
    RawCurses::WALL_NSEW = ACS_PLUS;

    ::endwin();
};

// static storage
bool RawCurses::initialized = false;
int RawCurses::UP = 0;
int RawCurses::UP_RIGHT = 0;
int RawCurses::RIGHT = 0;
int RawCurses::DOWN_RIGHT = 0;
int RawCurses::DOWN = 0;
int RawCurses::DOWN_LEFT = 0;
int RawCurses::LEFT = 0;
int RawCurses::UP_LEFT = 0;
int RawCurses::WALL_NS = 0;
int RawCurses::WALL_EW = 0;
int RawCurses::WALL_NE = 0;
int RawCurses::WALL_SE = 0;
int RawCurses::WALL_SW = 0;
int RawCurses::WALL_NW = 0;
int RawCurses::WALL_NSE = 0;
int RawCurses::WALL_NSW = 0;
int RawCurses::WALL_NEW = 0;
int RawCurses::WALL_SEW = 0;
int RawCurses::WALL_NSEW = 0;
