#include "window.h"

#include "ncurses.h" // for COLOR_PAIR()

io::Window::Window(io::Screen& screen, 
                        RawCurses& curses,
                        unsigned int screen_row, 
                        unsigned int screen_cell, 
                        unsigned int num_rows, 
                        unsigned int num_cells) :
    screen_(screen), curses_(curses), screen_row_(screen_row), screen_cell_(screen_cell), 
    height_(num_rows), width_(num_cells), window_(nullptr)
{
    this->window_ = this->curses_.newwin( num_rows, num_cells, screen_row, screen_cell);
}

io::Window::~Window()
{
    this->curses_.delwin(this->window_);
    this->window_ = nullptr;
}

void io::Window::place_character(unsigned int row,
                                        unsigned int cell,
                                        unsigned int character,
                                        unsigned int color_pair_index)
{
    // todo this should be in screen (and cached)
    this->curses_.start_color();

    // todo this should be in screen (and cached)
    this->curses_.attron_m(COLOR_PAIR(color_pair_index));

    this->curses_.mvwaddch_m(this->window_, row, cell, character);

    // todo this should be in screen (and cached)
    this->curses_.attroff_m(COLOR_PAIR(color_pair_index));
}

void io::Window::refresh()
{
    this->curses_.wrefresh(this->window_);
}
