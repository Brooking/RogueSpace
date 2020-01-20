#include "window.h"

io::Window::Window(
    std::shared_ptr<iScreen> screen, 
    unsigned int screen_row, 
    unsigned int screen_cell, 
    unsigned int num_rows, 
    unsigned int num_cells) :
    screen_(screen),
    height_(num_rows), width_(num_cells), curses_window_(nullptr)
{
    this->curses_window_ = this->screen_->curses()->newwin(
        static_cast<int>(num_rows),
        static_cast<int>(num_cells),
        static_cast<int>(screen_row),
        static_cast<int>(screen_cell));
}

io::Window::~Window()
{
    this->screen_->curses()->delwin(this->curses_window_);
    this->curses_window_ = nullptr;
}

void io::Window::place_character(
    unsigned int row,
    unsigned int cell,
    unsigned int character,
    io::Color foreground,
    io::Color background)
{
    int colored_character = this->screen_->get_color_character(
        character, 
        foreground, 
        background);
    this->screen_->curses()->mvwaddch_m(
        this->curses_window_, 
        static_cast<int>(row), 
        static_cast<int>(cell), 
        static_cast<unsigned long>(colored_character));
}

void io::Window::place_string(
    unsigned int row,
    unsigned int cell,
    std::string string,
    io::Color foreground,
    io::Color background)
{
    for (unsigned int i = 0; i < string.size(); i++)
    {
        this->place_character(row, cell+i, static_cast<unsigned int>(string[i]), foreground, background);
    }
}

void io::Window::refresh()
{
    this->screen_->curses()->wrefresh(this->curses_window_);
}
