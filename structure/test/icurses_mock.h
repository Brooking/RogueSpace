#ifndef _icurses_mock_h_
#define _icurses_mock_h_

#include "icurses.h"

class iCursesMock : public iCurses
{
public:
    iCursesMock(bool* destructor_called) : destructor_called(destructor_called) {}
    virtual ~iCursesMock()
    {
        *(this->destructor_called) = true;
    }

    // none of these are functional
    virtual void* initscr() override {return nullptr; }
    virtual int endwin() override {return 0;}
    virtual int noecho() override {return 0;}
    virtual int cbreak() override {return 0;}
    virtual int keypad(void* screen, bool enable_extended_single_value) override {return 0;}
    virtual int clear() override {return 0;}
    virtual int curs_set(int visibility) override {return 0;}
    virtual void getmaxyx_m(void* screen, int& y, int& x) override {}
    virtual bool has_colors() override {return false;}
    virtual int start_color() override {return 0;}
    virtual int init_pair(short index, short foreground, short background) override {return 0;}
    virtual int attron_m(int attributes) override {return 0;}
    virtual int attroff_m(int attributes) override {return 0;}
    virtual int mvwaddch_m(void* window, int y, int x, unsigned long ch) override {return 0;}
    virtual int getch_m() override {return 0;}
    virtual int printw(const char * message) override {return 0;}
    virtual void* newwin(int nlines, int ncols, int begin_y, int begin_x) override {return nullptr;}
    virtual int delwin(void* window) override {return 0;}
    virtual int wrefresh(void* window) override {return 0;}
    virtual void* stdscr_m() override {return nullptr;}

private:
    bool* destructor_called;

};

#endif // _icurses_mock_h_
