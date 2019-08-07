#ifndef _rawcurses_h_
#define _rawcurses_h_

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

/*static:*/

    // keys
    static const unsigned long UP;
    static const unsigned long UP_RIGHT;
    static const unsigned long RIGHT;
    static const unsigned long DOWN_RIGHT;
    static const unsigned long DOWN;
    static const unsigned long DOWN_LEFT;
    static const unsigned long LEFT;
    static const unsigned long UP_LEFT;

    // special characters
    static const unsigned long WALL_NS;
    static const unsigned long WALL_EW;
    static const unsigned long WALL_NE;
    static const unsigned long WALL_SE;
    static const unsigned long WALL_SW;
    static const unsigned long WALL_NW;
    static const unsigned long WALL_NSE;
    static const unsigned long WALL_NSW;
    static const unsigned long WALL_NEW;
    static const unsigned long WALL_SEW;
    static const unsigned long WALL_NSEW;

    static const unsigned long BULLET;

private:
    static void validate_statics();
};

#endif // _rawcurses_h_