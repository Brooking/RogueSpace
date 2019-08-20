#ifndef _io_screen_h_
#define _io_screen_h_

#include <map>
#include "io_constants.h"

namespace io
{

class Window;
class RawCurses;

//
// A singleton representing the screen
//
class Screen
{
public:
    // creator
    static io::Screen* open_screen(io::RawCurses& curses);

    // deleter
    static void close_screen(io::Screen& screen);

    // Print a colored message to the screen
    void add(const char* Message, io::Color foreground, 
        io::Color background = io::Color::BLACK);

    // Print a message to the screen
    void add(const char* Message);

    // accessors
    int width();
    int height();

    // create a window
    io::Window* create_window(
        unsigned int screen_row, 
        unsigned int screen_cell, 
        unsigned int num_rows, 
        unsigned int num_cells);

    // wait for a character
    unsigned int get_key_input();

    // get a colored character
    unsigned int get_color_character(unsigned int character, io::Color foreground, io::Color background);

private:
    // Initialize the screen
    Screen(io::RawCurses& curses);

    // tear down the screen
    ~Screen();

    // fetch and cache a color pair index for these colors
    unsigned int get_colorpair_index(io::Color foreground, io::Color background);

private:
    io::RawCurses& curses_;
    int width_;
    int height_;
    unsigned int color_pair_index_;

    static int ref_count;
    static io::Screen* singleton;

    // index is pair<foreground,background>, value is index
    std::map<std::pair<io::Color,io::Color>,int> color_pairs_;
    int next_color_pair_index_;
};

} // namespace io

#endif // _io_screen_h_
