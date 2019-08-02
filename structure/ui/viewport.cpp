#include <bitset>
#include "viewport.h"
#include "icon.h"

Viewport::Viewport(iCurses& curses, Screen& screen, iFloor& floor, Location center) : 
    curses_(curses), screen_(screen), floor_(floor), anchor_(Location())
{
    this->parent_window_ = curses_.newwin(floor_.height(), floor_.width(), 0, 0);
    this->full_update();
    this->curses_.wrefresh(this->parent_window_);

    // size and position the child window
    this->child_window_ = curses_.derwin(this->parent_window_, this->screen_.height(), this->screen_.width(), 0, 0);
    this->update_center(center);
    this->refresh();;
}

bool Viewport::update_center(Location center)
{
    int anchor_row = std::max(0, center.row() - this->screen_.height() / 2);
    int anchor_cell = std::max(0, center.cell() - this->screen_.width() / 2);
    this->anchor_ = Location(anchor_row, anchor_cell);

    this->curses_.mvderwin(this->child_window_, this->anchor_.row(), this->anchor_.cell());

    return true;
}

bool Viewport::full_update()
{
    for (int row = 0; row < this->floor_.height(); row++)
    {
        for (int cell = 0; cell < this->floor_.width(); cell++)
        {
            this->update(Location(row,cell));
        }
    }

    return true;
}

bool Viewport::update(Location location)
{
    UIToken token = this->floor_.token(location);
    std::bitset<8> adjacency;
    if (token == UIToken::wall)
    {
        adjacency[AdjacentWallBits::North] = this->floor_.token(Location(location.row()-1, location.cell())) == UIToken::wall;
        adjacency[AdjacentWallBits::East] = this->floor_.token(Location(location.row(), location.cell()+1)) == UIToken::wall;
        adjacency[AdjacentWallBits::South] = this->floor_.token(Location(location.row()+1, location.cell())) == UIToken::wall;
        adjacency[AdjacentWallBits::West] = this->floor_.token(Location(location.row(), location.cell()-1)) == UIToken::wall;
    }
    Icon icon(token, static_cast<int>(adjacency.to_ulong()));
    this->curses_.start_color();
    this->curses_.attron_m(icon.color_pair());
    this->curses_.mvwaddch_m(this->parent_window_, location.row(), location.cell(), icon.symbol());
    this->curses_.attroff_m(icon.color_pair());
    return true;
}

bool Viewport::refresh()
{
    this->curses_.wrefresh(this->parent_window_);
    this->curses_.wrefresh(this->child_window_);
    return true;
}