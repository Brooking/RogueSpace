#include "generator.h"
#include "../world/bee.h"
#include "../world/dog.h"
#include "../world/rat.h"
#include "../world/wall.h"

void wall_border(std::shared_ptr<Floor>);

std::shared_ptr<Floor> make_mini(
    std::shared_ptr<io::Screen> screen, 
    std::shared_ptr<Hero>& hero, 
    std::vector<std::shared_ptr<iThing>>& monsters)
{
    // create a floor
    std::shared_ptr<Floor> floor = Floor::create(7, 7);

    // put our dude on the floor in upper left
    Location starting_spot(1,1);
    std::shared_ptr<Tile> starting_tile = floor->tile(starting_spot);
    hero = std::make_shared<Hero>(/*sight_range*/1);
    hero->place(starting_tile);

    // put a wall around the outside
    wall_border(floor);

    // add a light in the  lower right corner
    floor->add_light(floor->height()-2, floor->width()-2, 2);

    return floor;
}

std::shared_ptr<Floor> make_standard(
    std::shared_ptr<io::Screen> screen, 
    std::shared_ptr<Hero>& hero, 
    std::vector<std::shared_ptr<iThing>>& monsters)
{
    // create a floor larger than the view area
    std::shared_ptr<Floor> floor = Floor::create(screen->height(), screen->width());

    // put our dude on the floor in the center
    Location starting_spot(floor->height()/2, floor->width()/2);
    std::shared_ptr<Tile> starting_tile = floor->tile(starting_spot);
    hero = std::make_shared<Hero>(/*sight_range*/5);
    hero->place(starting_tile);

    // wall the border
    wall_border(floor);

    std::shared_ptr<Wall> wall;
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

    // add a lights in the upper and lower right corner...
    floor->add_light(1, floor->width()-2, 10);
    floor->add_light(floor->height()-2, floor->width()-2, 10);

    // ...and the left wall
    floor->add_light(floor->height()/2-1, 1, 15);

    // add monsters
    std::shared_ptr<Rat> rat = std::make_shared<Rat>();
    rat->place(floor->tile(Location(floor->height()/2, floor->width()-2)));
    monsters.push_back(rat);

    std::shared_ptr<Bee> bee = std::make_shared<Bee>();
    bee->place(floor->tile(Location(3 * floor->height()/4, floor->width()/4)));
    monsters.push_back(bee);

    // add a dog
    std::shared_ptr<Dog> dog = std::make_shared<Dog>();
    dog->place(floor->tile(Location(starting_spot.row(), starting_spot.cell()+1)));
    monsters.push_back(dog);

    return floor;
}

std::shared_ptr<Floor> make_full(
    std::shared_ptr<io::Screen> screen, 
    std::shared_ptr<Hero>& hero, 
    std::vector<std::shared_ptr<iThing>>& monsters)
{
    assert(false);
}

void wall_border(std::shared_ptr<Floor> floor)
{
    std::shared_ptr<Wall> wall;
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
}
