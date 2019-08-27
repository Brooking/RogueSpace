#include "window.h"

io::Window::Window(
    io::Screen& screen, 
    std::shared_ptr<RawCurses> curses,
    unsigned int screen_row, 
    unsigned int screen_cell, 
    unsigned int num_rows, 
    unsigned int num_cells) :
    screen_(screen), curses_(curses), screen_row_(screen_row), screen_cell_(screen_cell), 
    height_(num_rows), width_(num_cells), window_(nullptr)
{
    this->window_ = this->curses_->newwin( num_rows, num_cells, screen_row, screen_cell);
}

io::Window::~Window()
{
    this->curses_->delwin(this->window_);
    this->window_ = nullptr;
}

void io::Window::place_character(
    unsigned int row,
    unsigned int cell,
    unsigned int character,
    io::Color foreground,
    io::Color background)
{
    unsigned int colored_character = this->screen_.get_color_character(character, foreground, background);
    this->curses_->mvwaddch_m(this->window_, row, cell, colored_character);
}

void io::Window::refresh()
{
    this->curses_->wrefresh(this->window_);
}
