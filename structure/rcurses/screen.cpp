#include <assert.h>
#include "window.h" 
#include "screen.h"

// static variables
int rcurses::Screen::ref_count = 0;
rcurses::Screen* rcurses::Screen::singleton = nullptr;

rcurses::Screen* rcurses::Screen::open_screen(RawCurses& curses)
{
    if (rcurses::Screen::singleton == nullptr)
    {
        assert(rcurses::Screen::ref_count == 0);
        rcurses::Screen::singleton = new Screen(curses);
    }
    else
    {
        // todo we should not be switching curses
        // assert(curses == rcurses::Screen::singleton->curses_);
    }

    rcurses::Screen::ref_count++;
    return rcurses::Screen::singleton;
}

void rcurses::Screen::close_screen(rcurses::Screen& screen)
{
    assert(rcurses::Screen::singleton != nullptr);
    assert(rcurses::Screen::ref_count > 0);

    if (--rcurses::Screen::ref_count == 0)
    {
        delete rcurses::Screen::singleton;
        rcurses::Screen::singleton = nullptr;
    }
}

rcurses::Screen::Screen(RawCurses& curses) : curses_(curses)
{
    // initialize the ncurses library
    curses_.initscr();

    // do not echo keyboard input to the screen
    curses_.noecho();

    // pass keys directly to the program (without buffering)
    // convert ctrl-z, interrupt, and ctlr-c into signals
    curses_.cbreak();

    // enable reading F1-F12 and arrow keys
    curses_.keypad(curses_.stdscr_m(), true);

    // clear the screen
    curses_.clear();

    // set the cursor to invisible
    curses_.curs_set(0);

    // fetch the screen size
    curses_.getmaxyx_m(curses_.stdscr_m(), this->height_, this->width_);

    // check for colors
    if (!curses_.has_colors())
    {
        this->add("no colors");
    }

    // enable colors
    curses_.start_color();
}

rcurses::Screen::~Screen()
{
    // close the curses library
    curses_.endwin();
}

void rcurses::Screen::add(const char* Message)
{
    curses_.printw(Message);
}

int rcurses::Screen::height()
{
    return this->height_;
}

int rcurses::Screen::width()
{
    return this->width_;
}

rcurses::Window* rcurses::Screen::create_window(unsigned int screen_row, 
                                                unsigned int screen_cell, 
                                                unsigned int num_rows, 
                                                unsigned int num_cells)
{
    return new rcurses::Window(*this, this->curses_, screen_row, screen_cell, num_rows, num_cells);
}                        

unsigned int rcurses::Screen::get_key_input()
{
    return this->curses_.getch_m();
}