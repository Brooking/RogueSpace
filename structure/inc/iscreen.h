#ifndef _iscreen_h_
#define _iscreen_h_

#include <memory>
#include "icurses.h"
#include "io_constants.h"
#include "iwindow.h"

//
// Interface to the raw screen
//
class iScreen
{
public:
    virtual ~iScreen() {}

    // Print a colored message to the screen
    virtual void add(
        const char* Message,
        io::Color foreground, 
        io::Color background = io::Color::BLACK) = 0;

    // Print a message to the screen
    virtual void add(const char* Message) = 0;

    // accessors
    virtual unsigned int width() const = 0;
    virtual unsigned int height() const = 0;

    // create a window
    virtual std::shared_ptr<iWindow> create_window(
        unsigned int screen_row, 
        unsigned int screen_cell, 
        unsigned int num_rows, 
        unsigned int num_cells) = 0;

    // wait for a character
    virtual unsigned int get_key_input() = 0;

    // get a colored character
    // (because the screen is where we cache color pairs)
    virtual unsigned int get_color_character(
        unsigned int character,
        io::Color foreground,
        io::Color background) = 0;

    // get our curses interface
    virtual std::shared_ptr<iCurses> curses() const = 0;
};

#endif // _iscreen_h_