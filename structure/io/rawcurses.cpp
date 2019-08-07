#include <ncurses.h>
#include <assert.h>
#include "rawcurses.h"
#include "io_constants.h"

io::RawCurses::RawCurses()
{
    io::RawCurses::validate_io_constants();
}

void* io::RawCurses::initscr()
{
    return ::initscr();
}

int io::RawCurses::endwin()
{
    return ::endwin();
}

int io::RawCurses::noecho()
{
    return ::noecho();
}

int io::RawCurses::cbreak()
{
    return ::cbreak();
}

int io::RawCurses::keypad(void* screen, bool enable_extended_single_value)
{
    return ::keypad((WINDOW*)screen, enable_extended_single_value);
}

int io::RawCurses::clear()
{
    return ::clear();
}

int io::RawCurses::curs_set(int visibility)
{
    return ::curs_set(visibility);
}

void io::RawCurses::getmaxyx_m(void* window, int& y, int& x)
{
    // call the macro
    getmaxyx((WINDOW*)window, y, x);
}

bool io::RawCurses::has_colors()
{
    return ::has_colors();
}

int io::RawCurses::start_color()
{
    return ::start_color();
}

int io::RawCurses::init_pair(short index, short foreground, short background)
{
    return ::init_pair(index, foreground, background);
}

int io::RawCurses::attron_m(int attributes)
{
    // call the macro
    return attron(attributes);
}

int io::RawCurses::attroff_m(int attributes)
{
    // call the macro
    return attroff(attributes);
}

int io::RawCurses::mvwaddch_m(void* window, int y, int x, unsigned long ch)
{
    // call the macro
    return mvwaddch((WINDOW*)window, y, x, ch);
}

int io::RawCurses::getch_m()
{
    return getch();
}

int io::RawCurses::printw(const char * message)
{
    return ::printw(message);
}

void* io::RawCurses::newwin(int nlines, int ncols, int begin_y, int begin_x)
{
    return (void*)::newwin(nlines, ncols, begin_y, begin_x);
}

int io::RawCurses::delwin(void* window)
{
    return ::delwin((WINDOW*)window);
}

int io::RawCurses::wrefresh(void* window)
{
    return ::wrefresh((WINDOW*)window);
}

void* io::RawCurses::stdscr_m()
{
    return ::stdscr;
}

// initialize static variables
void io::RawCurses::validate_io_constants()
{
    // in order for the curses macros to be correct, we must call the curses initializer
    // but the class does not yet exist, so use the raw one
    ::initscr();    

    // set our local key statics
    assert(io::Key::UP == static_cast<unsigned int>(KEY_UP));
    assert(io::Key::UP_RIGHT == static_cast<unsigned int>(KEY_PPAGE));
    assert(io::Key::RIGHT == static_cast<unsigned int>(KEY_RIGHT));
    assert(io::Key::DOWN_RIGHT == static_cast<unsigned int>(KEY_NPAGE));
    assert(io::Key::DOWN == static_cast<unsigned int>(KEY_DOWN));
    assert(io::Key::DOWN_LEFT == static_cast<unsigned int>(KEY_END));
    assert(io::Key::LEFT == static_cast<unsigned int>(KEY_LEFT));
    assert(io::Key::UP_LEFT == static_cast<unsigned int>(KEY_HOME));

    // set our local character statics
    assert(io::Character::WALL_NS == static_cast<unsigned int>(ACS_VLINE));
    assert(io::Character::WALL_EW == static_cast<unsigned int>(ACS_HLINE));
    assert(io::Character::WALL_NE == static_cast<unsigned int>(ACS_LLCORNER));
    assert(io::Character::WALL_SE == static_cast<unsigned int>(ACS_ULCORNER));
    assert(io::Character::WALL_SW == static_cast<unsigned int>(ACS_URCORNER));
    assert(io::Character::WALL_NW == static_cast<unsigned int>(ACS_LRCORNER));
    assert(io::Character::WALL_NSE == static_cast<unsigned int>(ACS_LTEE));
    assert(io::Character::WALL_NSW == static_cast<unsigned int>(ACS_RTEE));
    assert(io::Character::WALL_NEW == static_cast<unsigned int>(ACS_BTEE));
    assert(io::Character::WALL_SEW == static_cast<unsigned int>(ACS_TTEE));
    assert(io::Character::WALL_NSEW == static_cast<unsigned int>(ACS_PLUS));

    assert(io::Character::BULLET == static_cast<unsigned int>(ACS_BULLET));


    ::endwin();
};
