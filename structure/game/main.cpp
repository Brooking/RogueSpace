#include <iostream>
#include <map>
#include <memory>
#include "io_constants.h"
#include "../io/screen.h"
#include "../io/rawcurses.h"
#include "../world/floor.h"
#include "../world/hero.h"
#include "../world/rat.h"
#include "../world/bee.h"
#include "../world/dog.h"
#include "../ui/viewport.h"
#include "../world/wall.h"

void game_loop(std::shared_ptr<Viewport> viewport, std::shared_ptr<Hero> hero, std::vector<std::shared_ptr<iThing>> monsters);
void fill_floor(std::shared_ptr<Floor> floor, std::shared_ptr<Hero> hero);

int main()
{
    // initialize the screen
    std::shared_ptr<io::RawCurses> curses = std::make_shared<io::RawCurses>();
    std::shared_ptr<io::Screen> screen = io::Screen::open_screen(curses);

    // Print a welcome message and wait until the user presses a key
    screen->add("Welcome to the RogueSpace(tm) game.\nPress any key to start.\nIf you want to quit, press \"Q\"");
    int ch = screen->get_key_input();
    if (ch == 'q' || ch == 'Q') 
    {
        // todo this should be done by screen destructor
        curses->endwin();
        return 0;
    }

    // create a floor larger than the view area
    std::shared_ptr<Floor> floor = Floor::create(screen->height()*1.5, screen->width()*1.5);

    // put our dude on the floor in the center
    Location starting_spot(floor->height()/2, floor->width()/2);
    std::shared_ptr<Tile> starting_tile = floor->tile(starting_spot);
    std::shared_ptr<Hero> hero = std::make_shared<Hero>(/*sight_range*/5);
    hero->place(starting_tile);

    // fill in the walls and lights
    fill_floor(floor, hero);

    // add monsters
    std::vector<std::shared_ptr<iThing>> monsters;
    std::shared_ptr<Rat> rat = std::make_shared<Rat>();
    rat->place(floor->tile(Location(floor->height()/4, floor->width()/4)));
    monsters.push_back(rat);

    std::shared_ptr<Bee> bee = std::make_shared<Bee>();
    bee->place(floor->tile(Location(3 * floor->height()/4, floor->width()/4)));
    monsters.push_back(bee);

    // add a dog
    std::shared_ptr<Dog> dog = std::make_shared<Dog>();
    dog->place(floor->tile(Location(starting_spot.row(), starting_spot.cell()+1)));
    monsters.push_back(dog);

    // create a viewport on that floor that is the full viewable area
    std::shared_ptr<Viewport> viewport = 
        std::make_shared<Viewport>(screen, floor, screen->height(), screen->width(), starting_spot.row(), starting_spot.cell());
    floor->register_update(viewport);

    // start the game loop
    game_loop(viewport, hero, monsters);

    // todo this should be done by screen destructor
    curses->endwin();
    return 0;
}

void game_loop(std::shared_ptr<Viewport> viewport, std::shared_ptr<Hero> hero, std::vector<std::shared_ptr<iThing>> monsters)
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

        hero->move(direction);
        for (auto& monster : monsters)
        {
            monster->move();
        }
        viewport->refresh();
    }
}

void fill_floor(std::shared_ptr<Floor> floor, std::shared_ptr<Hero> hero)
{
    std::shared_ptr<Wall> wall;
    // put walls around the outside
    for (int row = 0; row < floor->height(); row++)
    {
        if (row == 0 || row == floor->height()-1)
        {
            for (int cell = 0; cell < floor->width(); cell++)
            {
                wall = std::make_shared<Wall>();
                wall->place(floor->tile(Location(row,cell)));
            }
        }
        else
        {
            wall = std::make_shared<Wall>();
            wall->place(floor->tile(Location(row,0)));
            wall = std::make_shared<Wall>();
            wall->place(floor->tile(Location(row,floor->width()-1)));
        }
    }

    // put a wall with a door through the center
    int wall_cell = hero->where().cell()+1;
    for (int row = 1; row < hero->where().row(); row++)
    {
        wall = std::make_shared<Wall>();
        wall->place(floor->tile(Location(row, wall_cell)));
    }
    for (int row = hero->where().row()+1; row < floor->height()-1; row++)
    {
        wall = std::make_shared<Wall>();
        wall->place(floor->tile(Location(row, wall_cell)));
    }

    // make a pillar
    wall = std::make_shared<Wall>();
    wall->place(floor->tile(Location(2,floor->width()-3)));

    // diagonal walls
    for (int row = 1; row < floor->height()-1; row++)
    {
        if (row == hero->where().row())
        {
            continue;
        }

        // thin
        std::shared_ptr<Tile> tile = floor->tile(Location(row,row));
        if (tile->num_things() == 0)
        {
            wall = std::make_shared<Wall>();
            wall->place(tile);
        }

        // thick
        int cell = floor->width()/2 + row;
        tile = floor->tile(Location(row, cell));
        if (tile->num_things() == 0)
        {
            wall = std::make_shared<Wall>();
            wall->place(tile);
        }

        tile = floor->tile(Location(row, cell+1));
        if (tile->num_things() == 0)
        {
            wall = std::make_shared<Wall>();
            wall->place(tile);
        }
    }

    // add a lights in the upper and lower right corner
    floor->add_light(1, floor->width()-2, 10);
    floor->add_light(floor->height()-2, floor->width()-2, 10);

    // and the left wall
    floor->add_light(floor->height()/2-1, 1, 15);
}