#ifndef _io_screen_h_
#define _io_screen_h_

#include <map>
#include <memory>
#include <mutex>
#include "io_constants.h"
#include "icurses.h"

namespace io
{

class Window;

// std::enable_shared_from_this has an accessible non-virtual destructor
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

//
// A fake singleton representing the screen
// (it will throw if you ask for another...)
//
class Screen : public std::enable_shared_from_this<Screen>
{
public:
    // creator
    static std::shared_ptr<io::Screen> open_screen(std::shared_ptr<iCurses> curses);
    virtual ~Screen();

    // Print a colored message to the screen
    void add(const char* Message, io::Color foreground, 
        io::Color background = io::Color::BLACK);

    // Print a message to the screen
    void add(const char* Message);

    // accessors
    int width();
    int height();

    // create a window
    std::shared_ptr<io::Window> create_window(
        unsigned int screen_row, 
        unsigned int screen_cell, 
        unsigned int num_rows, 
        unsigned int num_cells);

    // wait for a character
    unsigned int get_key_input();

    // get a colored character
    unsigned int get_color_character(unsigned int character, io::Color foreground, io::Color background);

    // get our curses interface
    std::shared_ptr<iCurses> curses() { return this->curses_; }

private:
    // Initialize the screen
    Screen(std::shared_ptr<iCurses> curses);

    // fetch and cache a color pair index for these colors
    unsigned int get_colorpair_index(io::Color foreground, io::Color background);

    Screen() = delete;
    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

private:
    // singleton support
    static bool used;
    static std::mutex mutex;

    std::shared_ptr<iCurses> curses_;
    int width_;
    int height_;
    unsigned int color_pair_index_;


    // index is pair<foreground,background>, value is index
    std::map<std::pair<io::Color,io::Color>,int> color_pairs_;
    int next_color_pair_index_;
};

} // namespace io

#endif // _io_screen_h_
