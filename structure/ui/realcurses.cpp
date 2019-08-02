#include <ncurses.h>
#include "realcurses.h"

void* RealCurses::initscr()
{
    return ::initscr();
}

int RealCurses::endwin()
{
    return ::endwin();
}

int RealCurses::noecho()
{
    return ::noecho();
}

int RealCurses::cbreak()
{
    return ::cbreak();
}

int RealCurses::keypad(void* window, bool enable_extended_single_value)
{
    return ::keypad((WINDOW*)window, enable_extended_single_value);
}

int RealCurses::clear()
{
    return ::clear();
}

int RealCurses::curs_set(int visibility)
{
    return ::curs_set(visibility);
}

void RealCurses::getmaxyx_m(void* window, int& y, int& x)
{
    // call the macro
    getmaxyx((WINDOW*)window, y, x);
}

bool RealCurses::has_colors()
{
    return ::has_colors();
}

int RealCurses::start_color()
{
    return ::start_color();
}

int RealCurses::init_pair(short index, short foreground, short background)
{
    return ::init_pair(index, foreground, background);
}

int RealCurses::attron_m(int attributes)
{
    // call the macro
    return attron(attributes);
}

int RealCurses::attroff_m(int attributes)
{
    // call the macro
    return attroff(attributes);
}

int RealCurses::mvwaddch_m(void* window, int y, int x, char ch)
{
    // call the macro
    return mvwaddch((WINDOW*)window, y, x, ch);
}

int RealCurses::getch_m()
{
    return getch();
}

int RealCurses::printw(const char * message)
{
    return ::printw(message);
}

void* RealCurses::newwin(int nlines, int ncols, int begin_y, int begin_x)
{
    return (void*)::newwin(nlines, ncols, begin_y, begin_x);
}

void* RealCurses::derwin(void* orig, int nlines, int ncols, int begin_y, int begin_x)
{
    return (void*)::derwin((WINDOW*)orig, nlines, ncols, begin_y, begin_x);
}

int RealCurses::delwin(void* window)
{
    return ::delwin((WINDOW*)window);
}

int RealCurses::mvderwin(void* window, int y, int x)
{
    return ::mvderwin((WINDOW*)window, y, x);
}

int RealCurses::wrefresh(void* window)
{
    return ::wrefresh((WINDOW*)window);
}

void* RealCurses::stdscr_m()
{
    return ::stdscr;
}

int RealCurses::key_up()
{
    return KEY_UP;
}

int RealCurses::key_up_right()
{
    return KEY_A3;
}

int RealCurses::key_right()
{
    return KEY_RIGHT;
}

int RealCurses::key_down_right()
{
    return KEY_C3;
}

int RealCurses::key_down()
{
    return KEY_DOWN;
}

int RealCurses::key_down_left()
{
    return KEY_C1;
}

int RealCurses::key_left()
{
    return KEY_LEFT;
}

int RealCurses::key_up_left()
{
    return KEY_A1;    
}
