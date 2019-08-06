#include <iostream>
#include <map>
#include "../rcurses/rawcurses.h"
#include "../ui/screen.h"
#include "../world/floor.h"
#include "../world/hero.h"
#include "../ui/viewport.h"
#include "../world/wall.h"

void game_loop(RawCurses& curses, Viewport& viewport, Hero& hero);

// maps key inputs into useful directions
std::map<unsigned int,Direction> KeyToDirection
{
    {RawCurses::UP, Direction::North},
    {RawCurses::UP_RIGHT, Direction::NorthEast},
    {RawCurses::RIGHT, Direction::East},
    {RawCurses::DOWN_RIGHT, Direction::SouthEast},
    {RawCurses::DOWN, Direction::South},
    {RawCurses::DOWN_LEFT, Direction::SouthWest},
    {RawCurses::LEFT, Direction::West},
    {RawCurses::UP_LEFT, Direction::NorthWest},
};

int main()
{
    // initialize the screen
    RawCurses* curses = new RawCurses();
    Screen screen(*curses);

    // Print a welcome message and wait until the user presses a key
    screen.add("Welcome to the RogueSpace(tm) game.\nPress any key to start.\nIf you want to quit, press \"Q\"");
    int ch = curses->getch_m();
    if (ch == 'q' || ch == 'Q') 
    {
        return 0;
    }

    // create a floor larger than the view area
    Floor floor(screen.height()*1.5, screen.width()*1.5);

    // put our dude on the floor in the center
    Location starting_spot(floor.height()/2, floor.width()/2);
    Tile* starting_tile = floor.tile(starting_spot);
    Hero hero(starting_tile);

    // put walls around the outside
    // todo, these will leak, they should be unique_ptr attached to tiles
    for (int row = 0; row < floor.height(); row++)
    {
        if (row == 0 || row == floor.height()-1)
        {
            for (int cell = 0; cell < floor.width(); cell++)
            {
                new Wall(floor.tile(Location(row,cell)));
            }
        }
        else
        {
            new Wall(floor.tile(Location(row,0)));
            new Wall(floor.tile(Location(row,floor.width()-1)));
        }
    }

    // put a wall with a door through the center
    int wall_cell = hero.where().cell()+1;
    for (int row = 1; row < hero.where().row(); row++)
    {
        new Wall(floor.tile(Location(row, wall_cell)));
    }
    for (int row = hero.where().row()+1; row < floor.height()-1; row++)
    {
        new Wall(floor.tile(Location(row, wall_cell)));
    }

    // make a pillar
    new Wall (floor.tile(Location(2,floor.width()-3)));

    // diagonal walls
    for (int row = 1; row < floor.height()-1; row++)
    {
        if (row == hero.where().row())
        {
            continue;
        }

        // thin
        Tile* tile = floor.tile(Location(row,row));
        if (tile->num_things() == 0)
        {
            new Wall(tile);
        }

        // thick
        int cell = floor.width()/2 + row;
        tile = floor.tile(Location(row, cell));
        if (tile->num_things() == 0)
        {
            new Wall(tile);
        }

        tile = floor.tile(Location(row, cell+1));
        if (tile->num_things() == 0)
        {
            new Wall(tile);
        }
    }

    // create a viewport on that floor that is the full viewable area
    Viewport viewport(*curses, floor, screen.height(), screen.width(), starting_spot);
    floor.register_update(&viewport);

    // start the game loop
    game_loop(*curses, viewport, hero);

    return 0;
}

void game_loop(RawCurses& curses, Viewport& viewport, Hero& hero)
{
    int ch;
    bool done = false;
    while(!done) 
    {
        // get and decode input
        ch = curses.getch_m();
        Direction direction = Direction::none;
        if (KeyToDirection.count(ch) > 0)
        {
            direction = KeyToDirection[ch];
        }
        else
        {
            switch(ch)
            {
                case 'q':
                case 'Q':
                    done = true;
                    continue;

                case ' ':
                    // space is stand for a turn
                    break;

                default:
                    // for anything else, we go back for more input
                    continue;
            }
        }

        hero.move(direction);
        viewport.refresh();
    }
}