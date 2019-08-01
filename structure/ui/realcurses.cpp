#include <ncurses.h>
#include "realcurses.h"

void* Curses::initscr()
{
    return ::initscr();
}

int Curses::endwin()
{
    return ::endwin();
}

int Curses::noecho()
{
    return ::noecho();
}

int Curses::cbreak()
{
    return ::cbreak();
}

int Curses::keypad(void* window, bool enable_extended_single_value)
{
    return ::keypad((WINDOW*)window, enable_extended_single_value);
}

int Curses::clear()
{
    return ::clear();
}

int Curses::curs_set(int visibility)
{
    return ::curs_set(visibility);
}

void Curses::getmaxyx_m(void* window, int& y, int& x)
{
    // call the macro
    getmaxyx((WINDOW*)window, y, x);
}

bool Curses::has_colors()
{
    return ::has_colors();
}

int Curses::start_color()
{
    return ::start_color();
}

int Curses::init_pair(short index, short foreground, short background)
{
    return ::init_pair(index, foreground, background);
}

int Curses::attron_m(int attributes)
{
    // call the macro
    return attron(attributes);
}

int Curses::attroff_m(int attributes)
{
    // call the macro
    return attroff(attributes);
}

int Curses::mvwaddch_m(void* window, int y, int x, char ch)
{
    // call the macro
    return mvwaddch((WINDOW*)window, y, x, ch);
}

int Curses::getch_m()
{
    return getch();
}

int Curses::printw(const char * message)
{
    return ::printw(message);
}

void* Curses::newwin(int nlines, int ncols, int begin_y, int begin_x)
{
    return (void*)::newwin(nlines, ncols, begin_y, begin_x);
}

void* Curses::derwin(void* orig, int nlines, int ncols, int begin_y, int begin_x)
{
    return (void*)::derwin((WINDOW*)orig, nlines, ncols, begin_y, begin_x);
}

int Curses::delwin(void* window)
{
    return ::delwin((WINDOW*)window);
}

int Curses::mvderwin(void* window, int y, int x)
{
    return ::mvderwin((WINDOW*)window, y, x);
}

// todo remove the _m
void* Curses::stdscr_m()
{
    return ::stdscr;
}
