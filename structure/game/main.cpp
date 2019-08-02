#include "../ui/icurses.h"
#include "../ui/realcurses.h"
#include "../ui/screen.h"
#include "../world/floor.h"
#include "../world/hero.h"
#include "../ui/viewport.h"

void game_loop(int ch, iCurses& curses, Viewport& viewport, Hero& hero);

int main()
{
    // initialize the screen
    iCurses* curses = new RealCurses();
    Screen screen(*curses);

    // Print a welcome message and wait until the user presses a key
    screen.add("Welcome to the RR game.\nPress any key to start.\nIf you want to quit, press \"Q\"");
    int ch = curses->getch_m();

    // create a floor half the size of the view area
    Floor floor(screen.height()/2, screen.width()/2);

    // put our dude on the floor in the center
    Location starting_spot(floor.height()/2, floor.width()/2);
    Tile* starting_tile = floor.tile(starting_spot);
    Hero hero(starting_tile);

    // create a viewport on that floor that is the full viewable area
    Viewport viewport(*curses, screen, floor, starting_spot);
    floor.register_update(&viewport);

    // start the game loop
    game_loop(ch, *curses, viewport, hero);

    return 0;
}

void game_loop(int ch, iCurses& curses, Viewport& viewport, Hero& hero)
{
    // check for quit
    if (ch == 'q' || ch == 'Q') {
        return;
    }

    bool done = false;
    while(!done) {

        // todo - diagonals are not working

        // get and decode input
        ch = curses.getch_m();
        Direction direction = Direction::none;
        if (ch == curses.key_up())
        {
            direction = Direction::North;
        }
        else if (ch == curses.key_up_right())
        {
            direction = Direction::NorthEast;
        }
        else if (ch == curses.key_right())
        {
            direction = Direction::East;
        }
        else if (ch == curses.key_down_right())
        {
            direction = Direction::SouthEast;
        }
        else if (ch == curses.key_down())
        {
            direction = Direction::South;
        }
        else if (ch == curses.key_down_left())
        {
            direction = Direction::SouthEast;
        }
        else if (ch == curses.key_left())
        {
            direction = Direction::West;
        }
        else if (ch == curses.key_up_left())
        {
            direction = Direction::NorthWest;
        }
        else if (ch == 'Q' || ch == 'q')
        {
            done = true;
            continue;
        }
        else
        {
            continue;            
        }
        
        hero.move(direction);
        viewport.refresh();
    }
}