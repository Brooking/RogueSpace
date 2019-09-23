#ifndef _icurses_h_
#define _icurses_h_

//
// Interface to a curses implementation
//
class iCurses
{
public:
    virtual ~iCurses() = default;
    virtual void* initscr()= 0;
    virtual int endwin()= 0;
    virtual int noecho()= 0;
    virtual int cbreak()= 0;
    virtual int keypad(void* screen, bool enable_extended_single_value)= 0;
    virtual int clear()= 0;
    virtual int curs_set(int visibility)= 0;
    virtual void getmaxyx_m(void* screen, unsigned int& y, unsigned int& x)= 0;
    virtual bool has_colors()= 0;
    virtual int start_color()= 0;
    virtual int init_pair(short index, short foreground, short background)= 0;
    virtual int attron_m(int attributes)= 0;
    virtual int attroff_m(int attributes)= 0;
    virtual int mvwaddch_m(void* window, int y, int x, unsigned long ch)= 0;
    virtual int getch_m()= 0;
    virtual int printw(const char * message)= 0;
    virtual void* newwin(int nlines, int ncols, int begin_y, int begin_x)= 0;
    virtual int delwin(void* window)= 0;
    virtual int wrefresh(void* window)= 0;
    virtual void* stdscr_m()= 0;
};

#endif // _icurses_h_
