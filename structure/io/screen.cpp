#include <assert.h>
#include "window.h" 
#include "screen.h"
#include "rawcurses.h"

#include "ncurses.h" // for COLOR_PAIR()

// static variables
int io::Screen::ref_count = 0;
io::Screen* io::Screen::singleton = nullptr;

io::Screen* io::Screen::open_screen(std::shared_ptr<RawCurses> curses)
{
    if (io::Screen::singleton == nullptr)
    {
        assert(io::Screen::ref_count == 0);
        io::Screen::singleton = new Screen(curses);
    }
    else
    {
        // todo we should not be switching curses
        // assert(curses == io::Screen::singleton->curses_);
    }

    io::Screen::ref_count++;
    return io::Screen::singleton;
}

void io::Screen::close_screen(io::Screen& screen)
{
    assert(io::Screen::singleton != nullptr);
    assert(io::Screen::ref_count > 0);

    if (--io::Screen::ref_count == 0)
    {
        delete io::Screen::singleton;
        io::Screen::singleton = nullptr;
    }
}

io::Screen::Screen(std::shared_ptr<RawCurses> curses) : 
    curses_(curses), width_(0), height_(0), color_pair_index_(0), next_color_pair_index_(1)
{
    // initialize the ncurses library
    curses_->initscr();

    // do not echo keyboard input to the screen
    curses_->noecho();

    // pass keys directly to the program (without buffering)
    // convert ctrl-z, interrupt, and ctlr-c into signals
    curses_->cbreak();

    // enable reading F1-F12 and arrow keys
    curses_->keypad(curses_->stdscr_m(), true);

    // clear the screen
    curses_->clear();

    // set the cursor to invisible
    curses_->curs_set(0);

    // fetch the screen size
    curses_->getmaxyx_m(curses_->stdscr_m(), this->height_, this->width_);

    // check for colors
    if (!curses_->has_colors())
    {
        this->add("no colors");
    }

    // enable colors
    curses_->start_color();
}

io::Screen::~Screen()
{
    // close the curses library
    curses_->endwin();
}

void io::Screen::add(const char* Message, io::Color foreground, io::Color background)
{
    unsigned int color_pair_index = this->get_colorpair_index(foreground, background);
    curses_->attron_m(COLOR_PAIR(color_pair_index));
    add(Message);
    curses_->attroff_m(COLOR_PAIR(color_pair_index));
}

void io::Screen::add(const char* Message)
{
    curses_->printw(Message);
}

int io::Screen::height()
{
    return this->height_;
}

int io::Screen::width()
{
    return this->width_;
}

io::Window* io::Screen::create_window(
    unsigned int screen_row, 
    unsigned int screen_cell, 
    unsigned int num_rows, 
    unsigned int num_cells)
{
    return new io::Window(*this, this->curses_, screen_row, screen_cell, num_rows, num_cells);
}                        

unsigned int io::Screen::get_key_input()
{
    return this->curses_->getch_m();
}

unsigned int io::Screen::get_color_character(unsigned int character, io::Color foreground, io::Color background)
{
    unsigned int colorpair_index = this->get_colorpair_index(foreground, background);
    return character | COLOR_PAIR(colorpair_index);
}


unsigned int io::Screen::get_colorpair_index(io::Color foreground, io::Color background)
{
    assert(background >= io::Color::BLACK && background <= io::Color::WHITE);
    unsigned int color_pair_index = 0;
    std::pair<io::Color,io::Color> color_pair(foreground, background);
    if (this->color_pairs_.count(color_pair) == 0)
    {
        // new pair to us
        this->curses_->init_pair(this->next_color_pair_index_, foreground, background);
        color_pair_index = this->next_color_pair_index_;
        this->color_pairs_.insert(std::pair<std::pair<io::Color,io::Color>,int>(color_pair, color_pair_index));
        this->next_color_pair_index_++;
    }
    else
    {
        color_pair_index = this->color_pairs_[color_pair];
    }

    return color_pair_index;
}
