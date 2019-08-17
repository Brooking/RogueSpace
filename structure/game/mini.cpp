#include <iostream>
#include <map>
#include "../io/io_constants.h"
#include "../io/screen.h"
#include "../io/rawcurses.h"
#include "../world/floor.h"
#include "../world/hero.h"
#include "../world/rat.h"
#include "../world/dog.h"
#include "../ui/viewport.h"
#include "../world/wall.h"

void game_loop(Viewport& viewport, Hero& hero, std::vector<iThing*> monsters);
void fill_floor(Floor& floor, Hero& hero);

// maps key inputs into useful directions
std::map<unsigned int,Direction> KeyToDirection
{
    {io::Key::UP, Direction::North},
    {io::Key::UP_RIGHT, Direction::NorthEast},
    {io::Key::RIGHT, Direction::East},
    {io::Key::DOWN_RIGHT, Direction::SouthEast},
    {io::Key::DOWN, Direction::South},
    {io::Key::DOWN_LEFT, Direction::SouthWest},
    {io::Key::LEFT, Direction::West},
    {io::Key::UP_LEFT, Direction::NorthWest},
};

int main()
{
    // initialize the screen
    io::RawCurses* curses = new io::RawCurses();
    io::Screen* screen = io::Screen::open_screen(*curses);

    // Print a welcome message and wait until the user presses a key
    screen->add("Welcome to the mini RogueSpace(tm) game.\nPress any key to start.\nIf you want to quit, press \"Q\"");
    int ch = screen->get_key_input();
    if (ch == 'q' || ch == 'Q') 
    {
        return 0;
    }

    // create a floor
    Floor floor(7, 7);

    // put our dude on the floor in the center
    Location starting_spot(floor.height()/2, floor.width()/2);
    Tile* starting_tile = floor.tile(starting_spot);
    Hero hero(starting_tile, /*sight_range*/2);

    fill_floor(floor, hero);

    // create a viewport on that floor that is the full viewable area
    Viewport viewport(screen, floor, screen->height(), screen->width(), starting_spot.row(), starting_spot.cell());
    floor.register_update(&viewport);

    // start the game loop
    std::vector<iThing*> monsters;
    game_loop(viewport, hero, monsters);

    io::Screen::close_screen(*screen);
    screen = nullptr;
    return 0;
}

void game_loop(Viewport& viewport, Hero& hero, std::vector<iThing*> monsters)
{
    int ch;
    bool done = false;
    while(!done) 
    {
        // get and decode input
        ch = viewport.screen()->get_key_input();
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
        for (auto& monster : monsters)
        {
            monster->move();
        }
        viewport.refresh();
    }
}

void fill_floor(Floor& floor, Hero& hero)
{
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
    return;

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

    // add a lights in the upper and lower right corner
    floor.add_light(1, floor.width()-2, 20);
    floor.add_light(floor.height()-2, floor.width()-2, 20);
}