#ifndef _icon_h_
#define _icon_h_

#include "io_constants.h"
#include "uitoken.h"

//
// A container for a displayable ui icon
//
class Icon
{
public:
    Icon(UIToken token);
    virtual ~Icon() = default;

    // the foregound color
    io::Color foreground_color() { return this->foreground_color_; }

    // the foregound color
    io::Color background_color() { return this->background_color_; }

    // the symbol to show
    unsigned int symbol() { return this->symbol_; }

private:
    UIToken token_;
    io::Color foreground_color_;
    io::Color background_color_;
    unsigned int symbol_;
};

#endif // _icon_h_