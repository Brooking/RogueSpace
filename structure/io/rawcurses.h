#ifndef _rawcurses_h_
#define _rawcurses_h_

#include "icurses.h"

namespace io
{

//
// A class to wrap the actual ncurses implementation
//
class RawCurses : public iCurses
{
public:
    RawCurses();
    virtual ~RawCurses() {}

    virtual void* initscr() override;
    virtual int endwin() override;
    virtual int noecho() override;
    virtual int cbreak() override;
    virtual int keypad(void* screen, bool enable_extended_single_value) override;
    virtual int clear() override;
    virtual int curs_set(int visibility) override;
    virtual void getmaxyx_m(void* screen, int& y, int& x) override;
    virtual bool has_colors() override;
    virtual int start_color() override;
    virtual int init_pair(short index, short foreground, short background) override;
    virtual int attron_m(int attributes) override;
    virtual int attroff_m(int attributes) override;
    virtual int mvwaddch_m(void* window, int y, int x, unsigned long ch) override;
    virtual int getch_m() override;
    virtual int printw(const char * message) override;
    virtual void* newwin(int nlines, int ncols, int begin_y, int begin_x) override;
    virtual int delwin(void* window) override;
    virtual int wrefresh(void* window) override;
    virtual void* stdscr_m() override;

private:
    static void validate_io_constants();
};

} // namespace io

#endif // _rawcurses_h_