#ifndef _rawcurses_h_
#define _rawcurses_h_

namespace io
{

//
// A class to wrap the actual ncurses implementation
//
class RawCurses
{
public:
    RawCurses();
    virtual ~RawCurses() {}

    virtual void* initscr();
    virtual int endwin();
    virtual int noecho();
    virtual int cbreak();
    virtual int keypad(void* screen, bool enable_extended_single_value);
    virtual int clear();
    virtual int curs_set(int visibility);
    virtual void getmaxyx_m(void* screen, int& y, int& x);
    virtual bool has_colors();
    virtual int start_color();
    virtual int init_pair(short index, short foreground, short background);
    virtual int attron_m(int attributes);
    virtual int attroff_m(int attributes);
    virtual int mvwaddch_m(void* window, int y, int x, unsigned long ch);
    virtual int getch_m();
    virtual int printw(const char * message);
    virtual void* newwin(int nlines, int ncols, int begin_y, int begin_x);
    virtual int delwin(void* window);
    virtual int wrefresh(void* window);
    virtual void* stdscr_m();

private:
    static void validate_io_constants();
};

} // namespace io

#endif // _rawcurses_h_