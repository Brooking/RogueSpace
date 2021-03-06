#include <assert.h>
#include <ncurses.h>
#include "io_constants.h"
#include "rawcurses.h"

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

void io::RawCurses::getmaxyx_m(void* window, unsigned int& y, unsigned int& x)
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
    assert(static_cast<unsigned int>(io::Key::UP) == static_cast<unsigned int>(KEY_UP));
    assert(static_cast<unsigned int>(io::Key::UP_RIGHT) == static_cast<unsigned int>(KEY_PPAGE));
    assert(static_cast<unsigned int>(io::Key::RIGHT) == static_cast<unsigned int>(KEY_RIGHT));
    assert(static_cast<unsigned int>(io::Key::DOWN_RIGHT) == static_cast<unsigned int>(KEY_NPAGE));
    assert(static_cast<unsigned int>(io::Key::DOWN) == static_cast<unsigned int>(KEY_DOWN));
    assert(static_cast<unsigned int>(io::Key::DOWN_LEFT) == static_cast<unsigned int>(KEY_END));
    assert(static_cast<unsigned int>(io::Key::LEFT) == static_cast<unsigned int>(KEY_LEFT));
    assert(static_cast<unsigned int>(io::Key::UP_LEFT) == static_cast<unsigned int>(KEY_HOME));

    // set our local character statics
    assert(static_cast<unsigned int>(io::Character::WALL_NS) == static_cast<unsigned int>(ACS_VLINE));
    assert(static_cast<unsigned int>(io::Character::WALL_WE) == static_cast<unsigned int>(ACS_HLINE));
    assert(static_cast<unsigned int>(io::Character::WALL_NE) == static_cast<unsigned int>(ACS_LLCORNER));
    assert(static_cast<unsigned int>(io::Character::WALL_SE) == static_cast<unsigned int>(ACS_ULCORNER));
    assert(static_cast<unsigned int>(io::Character::WALL_SW) == static_cast<unsigned int>(ACS_URCORNER));
    assert(static_cast<unsigned int>(io::Character::WALL_NW) == static_cast<unsigned int>(ACS_LRCORNER));
    assert(static_cast<unsigned int>(io::Character::WALL_NSE) == static_cast<unsigned int>(ACS_LTEE));
    assert(static_cast<unsigned int>(io::Character::WALL_NSW) == static_cast<unsigned int>(ACS_RTEE));
    assert(static_cast<unsigned int>(io::Character::WALL_NWE) == static_cast<unsigned int>(ACS_BTEE));
    assert(static_cast<unsigned int>(io::Character::WALL_SWE) == static_cast<unsigned int>(ACS_TTEE));
    assert(static_cast<unsigned int>(io::Character::WALL_NSWE) == static_cast<unsigned int>(ACS_PLUS));

    assert(static_cast<unsigned int>(io::Character::BULLET) == static_cast<unsigned int>(ACS_BULLET));
    assert(static_cast<unsigned int>(io::Character::FROST) == static_cast<unsigned int>(ACS_CKBOARD));

    assert(static_cast<unsigned int>(io::Color::BLACK) == static_cast<unsigned int>(COLOR_BLACK));
    assert(static_cast<unsigned int>(io::Color::RED) == static_cast<unsigned int>(COLOR_RED));
    assert(static_cast<unsigned int>(io::Color::GREEN) == static_cast<unsigned int>(COLOR_GREEN));
    assert(static_cast<unsigned int>(io::Color::YELLOW) == static_cast<unsigned int>(COLOR_YELLOW));
    assert(static_cast<unsigned int>(io::Color::BLUE) == static_cast<unsigned int>(COLOR_BLUE));
    assert(static_cast<unsigned int>(io::Color::MAGENTA) == static_cast<unsigned int>(COLOR_MAGENTA));
    assert(static_cast<unsigned int>(io::Color::CYAN) == static_cast<unsigned int>(COLOR_CYAN));
    assert(static_cast<unsigned int>(io::Color::WHITE) == static_cast<unsigned int>(COLOR_WHITE));

    ::endwin();
}
