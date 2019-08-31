#include "window.h"

io::Window::Window(
    io::Screen& screen, 
    unsigned int screen_row, 
    unsigned int screen_cell, 
    unsigned int num_rows, 
    unsigned int num_cells) :
    screen_(screen), screen_row_(screen_row), screen_cell_(screen_cell), 
    height_(num_rows), width_(num_cells), window_(nullptr)
{
    this->window_ = this->screen_.curses()->newwin( num_rows, num_cells, screen_row, screen_cell);
}

io::Window::~Window()
{
    this->screen_.curses()->delwin(this->window_);
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
    this->screen_.curses()->mvwaddch_m(this->window_, row, cell, colored_character);
}

void io::Window::refresh()
{
    this->screen_.curses()->wrefresh(this->window_);
}
