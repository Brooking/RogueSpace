#ifndef _iwindow_h_
#define _iwindow_h_

class iWindow
{
public:
    virtual ~iWindow() = default;

    // place a colored character at the given spot in the window
    virtual void place_character(
        unsigned int row,
        unsigned int cell,
        unsigned int character,
        io::Color foreground,
        io::Color background) = 0;

    // push all changes to the actual screen
    virtual void refresh() = 0;

    // accessors
    virtual unsigned int height() const = 0;
    virtual unsigned int width() const = 0;

};

#endif // _iwindow_h_