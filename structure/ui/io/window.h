#ifndef _io_window_h_
#define _io_window_h_

#include "icurses.h"
#include "screen.h"

namespace io
{

class Window : public iWindow
{
public:
    // construct a window
    Window(
        std::shared_ptr<iScreen> screen,
        unsigned int screen_row, 
        unsigned int screen_cell, 
        unsigned int num_rows, 
        unsigned int num_cells);

    // destructor
    virtual ~Window();

    // iWindow: place a colored character at the given spot in the window
    void place_character(
        unsigned int row,
        unsigned int cell,
        unsigned int character,
        io::Color foreground,
        io::Color background) override;

    // iWindow: push all changes to the actual screen
    void refresh() override;

    // iWindow: height accessor
    unsigned int height() const override { return this->height_; }

    // iWindow: width accessor
    unsigned int width() const override { return this->width_; }

private:
    // prohibit parameterless construction
    Window() = delete;

    // prohibit copying
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

private:
    std::shared_ptr<iScreen> screen_;
    unsigned int screen_row_;
    unsigned int screen_cell_;
    unsigned int height_;
    unsigned int width_;
    void* curses_window_;
};

} // namespace io

#endif // _io_window_h_