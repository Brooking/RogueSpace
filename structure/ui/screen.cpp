#include "screen.h"
 
Screen::Screen(iCurses& curses) : curses_(curses) {
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
    if (!curses_.has_colors()) {
        this->add("no colors");
    }

    // enable colors
    curses_.start_color();
}

Screen::~Screen() {
    // close the curses library
    curses_.endwin();
}

void Screen::add(const char* Message) {
    curses_.printw(Message);
}

int Screen::height() {
    return this->height_;
}

int Screen::width() {
    return this->width_;
}
