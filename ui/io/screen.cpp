#include <assert.h>
#include "ncurses.h" // for COLOR_PAIR()
#include "icurses.h"
#include "screen.h"
#include "window.h" 

// static variables
bool io::Screen::used = false;
std::mutex io::Screen::mutex;

std::shared_ptr<iScreen> io::Screen::open_screen(std::shared_ptr<iCurses> curses)
{
    std::lock_guard<std::mutex> lock (io::Screen::mutex);
    if (io::Screen::used)
    {
        throw std::invalid_argument("second screen requested");
    }

    std::shared_ptr<io::Screen> screen = 
        std::shared_ptr<io::Screen>(new io::Screen(curses));
    used = true;
    return screen;
}

io::Screen::Screen(std::shared_ptr<iCurses> curses) : 
    curses_(curses), 
    width_(0), 
    height_(0), 
    color_pair_index_(0), 
    color_pairs_(), 
    next_color_pair_index_(1)
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

unsigned int io::Screen::height() const
{
    return this->height_;
}

unsigned int io::Screen::width() const
{
    return this->width_;
}

std::shared_ptr<iWindow> io::Screen::create_window(
    unsigned int screen_row, 
    unsigned int screen_cell, 
    unsigned int num_rows, 
    unsigned int num_cells)
{
    return std::make_shared<io::Window>(
        this->shared_from_this(), 
        screen_row, 
        screen_cell, 
        num_rows, 
        num_cells);
}                        

unsigned int io::Screen::get_key_input()
{
    return this->curses_->getch_m();
}

unsigned int io::Screen::get_color_character(
    unsigned int character, 
    io::Color foreground, 
    io::Color background)
{
    unsigned int colorpair_index = this->get_colorpair_index(foreground, background);
    return character | static_cast<unsigned int>(COLOR_PAIR(colorpair_index));
}


unsigned int io::Screen::get_colorpair_index(io::Color foreground, io::Color background)
{
    assert(background >= io::Color::BLACK && background <= io::Color::WHITE);
    unsigned int color_pair_index = 0;
    std::pair<io::Color,io::Color> color_pair(foreground, background);
    if (this->color_pairs_.count(color_pair) == 0)
    {
        // new pair to us
        this->curses_->init_pair(static_cast<short>(this->next_color_pair_index_), 
            static_cast<short>(foreground), static_cast<short>(background));
        color_pair_index = this->next_color_pair_index_;
        this->color_pairs_.insert(
            std::pair<std::pair<io::Color,io::Color>,int>(
                color_pair, 
                color_pair_index));
        this->next_color_pair_index_++;
    }
    else
    {
        color_pair_index = this->color_pairs_[color_pair];
    }

    return color_pair_index;
}
