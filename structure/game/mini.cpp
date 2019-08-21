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

void game_loop(std::shared_ptr<Viewport> viewport, Hero& hero, std::vector<iThing*> monsters);
void fill_floor(std::shared_ptr<Floor> floor, Hero& hero);

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
    std::shared_ptr<io::RawCurses> curses(new io::RawCurses());
    std::shared_ptr<io::Screen> screen = io::Screen::open_screen(curses);

    // Print a welcome message and wait until the user presses a key
    screen->add("Welcome to the ", io::Color::YELLOW, io::Color::BLACK);
    screen->add("mini RogueSpace", io::Color::BRIGHT_YELLOW, io::Color::BLACK);
    screen->add("(tm) game.\nPress any key to start.\nIf you want to quit, press \"Q\"\n\n",
        io::Color::YELLOW, io::Color::BLACK);

    screen->add("       BLACK ", io::Color::BLACK, io::Color::WHITE);
    screen->add("       RED ", io::Color::RED);
    screen->add("       GREEN ", io::Color::GREEN);
    screen->add("       YELLOW ", io::Color::YELLOW);
    screen->add("       BLUE ", io::Color::BLUE);
    screen->add("       MAGENTA ", io::Color::MAGENTA);
    screen->add("       CYAN ", io::Color::CYAN);
    screen->add("       WHITE\n", io::Color::WHITE);
    screen->add("BRIGHT_BLACK ", io::Color::BRIGHT_BLACK, io::Color::WHITE);
    screen->add("BRIGHT_RED ", io::Color::BRIGHT_RED);
    screen->add("BRIGHT_GREEN ", io::Color::BRIGHT_GREEN);
    screen->add("BRIGHT_YELLOW ", io::Color::BRIGHT_YELLOW);
    screen->add("BRIGHT_BLUE ", io::Color::BRIGHT_BLUE);
    screen->add("BRIGHT_MAGENTA ", io::Color::BRIGHT_MAGENTA);
    screen->add("BRIGHT_CYAN ", io::Color::BRIGHT_CYAN);
    screen->add("BRIGHT_WHITE\n", io::Color::BRIGHT_WHITE);
    screen->add("BRIGHT_BLACK ", io::Color::BRIGHT_BLACK, io::Color::BLACK);
    screen->add("BRIGHT_RED ", io::Color::BRIGHT_RED, io::Color::RED);
    screen->add("BRIGHT_GREEN ", io::Color::BRIGHT_GREEN, io::Color::GREEN);
    screen->add("BRIGHT_YELLOW ", io::Color::BRIGHT_YELLOW, io::Color::YELLOW);
    screen->add("BRIGHT_BLUE ", io::Color::BRIGHT_BLUE, io::Color::BLUE);
    screen->add("BRIGHT_MAGENTA ", io::Color::BRIGHT_MAGENTA, io::Color::MAGENTA);
    screen->add("BRIGHT_CYAN ", io::Color::BRIGHT_CYAN, io::Color::CYAN);
    screen->add("BRIGHT_WHITE\n", io::Color::BRIGHT_WHITE, io::Color::WHITE);

    int ch = screen->get_key_input();
    if (ch == 'q' || ch == 'Q') 
    {
        // todo this should be done by screen destructor
        curses->endwin();
        return 0;
    }

    // create a floor
    std::shared_ptr<Floor> floor(new Floor(7, 7));

    // put our dude on the floor in upper left
    Location starting_spot(1,1);
    std::shared_ptr<Tile> starting_tile = floor->tile(starting_spot);
    Hero hero(starting_tile, /*sight_range*/2);

    fill_floor(floor, hero);

    // create a viewport on that floor that is the full viewable area
    std::shared_ptr<Viewport> viewport(
        new Viewport(screen, floor, screen->height(), screen->width(), starting_spot.row(), starting_spot.cell()));
    floor->register_update(viewport);

    // start the game loop
    std::vector<iThing*> monsters;
    game_loop(viewport, hero, monsters);

    // todo this should be done by screen destructor
    curses->endwin();
    return 0;
}

void game_loop(std::shared_ptr<Viewport> viewport, Hero& hero, std::vector<iThing*> monsters)
{
    int ch;
    bool done = false;
    while(!done) 
    {
        // get and decode input
        ch = viewport->screen()->get_key_input();
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
        viewport->refresh();
    }
}

void fill_floor(std::shared_ptr<Floor> floor, Hero& hero)
{
    // put walls around the outside
    // todo, these will leak, they should be unique_ptr attached to tiles
    for (int row = 0; row < floor->height(); row++)
    {
        if (row == 0 || row == floor->height()-1)
        {
            for (int cell = 0; cell < floor->width(); cell++)
            {
                new Wall(floor->tile(Location(row,cell)));
            }
        }
        else
        {
            new Wall(floor->tile(Location(row,0)));
            new Wall(floor->tile(Location(row,floor->width()-1)));
        }
    }

    // add a light in the  lower right corner
    floor->add_light(floor->height()-2, floor->width()-2, 2);
    return;

    // put a wall with a door through the center
    int wall_cell = hero.where().cell()+1;
    for (int row = 1; row < hero.where().row(); row++)
    {
        new Wall(floor->tile(Location(row, wall_cell)));
    }
    for (int row = hero.where().row()+1; row < floor->height()-1; row++)
    {
        new Wall(floor->tile(Location(row, wall_cell)));
    }

    // make a pillar
    new Wall (floor->tile(Location(2,floor->width()-3)));

    // diagonal walls
    for (int row = 1; row < floor->height()-1; row++)
    {
        if (row == hero.where().row())
        {
            continue;
        }

        // thin
        std::shared_ptr<Tile> tile = floor->tile(Location(row,row));
        if (tile->num_things() == 0)
        {
            new Wall(tile);
        }

        // thick
        int cell = floor->width()/2 + row;
        tile = floor->tile(Location(row, cell));
        if (tile->num_things() == 0)
        {
            new Wall(tile);
        }

        tile = floor->tile(Location(row, cell+1));
        if (tile->num_things() == 0)
        {
            new Wall(tile);
        }
    }

    // add a lights in the upper and lower right corner
    floor->add_light(1, floor->width()-2, 20);
    floor->add_light(floor->height()-2, floor->width()-2, 20);
}