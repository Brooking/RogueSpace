#include "generator.h"
#include "../world/bee.h"
#include "../world/dog.h"
#include "../world/rat.h"
#include "../world/wall.h"
#include "../world/visibility/los.h"

void wall_border(std::shared_ptr<Floor>);
void make_wall(std::shared_ptr<Floor> floor, Location start, Location end);

std::shared_ptr<Floor> make_mini(
    std::shared_ptr<io::Screen>, 
    std::shared_ptr<Hero>& hero, 
    std::vector<std::shared_ptr<iThing>>&)
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
    for (unsigned int row = 1; row < hero->where().row(); row++)
    {
        wall = std::make_shared<Wall>();
        wall->place(floor->tile(Location(row, wall_cell)));
    }
    for (unsigned int row = hero->where().row()+1; row < floor->height()-1; row++)
    {
        wall = std::make_shared<Wall>();
        wall->place(floor->tile(Location(row, wall_cell)));
    }

    // make a pillar
    wall = std::make_shared<Wall>();
    wall->place(floor->tile(Location(2,floor->width()-3)));

    // diagonal walls
    for (unsigned int row = 1; row < floor->height()-1; row++)
    {
        if (row == static_cast<unsigned int>(hero->where().row()))
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
    // create a floor larger than the view area
    std::shared_ptr<Floor> floor = Floor::create(screen->height(), screen->width());

    // put our dude on the floor
    Location starting_spot(floor->height()/2, screen->width()/2);
    std::shared_ptr<Tile> starting_tile = floor->tile(starting_spot);
    hero = std::make_shared<Hero>(/*sight_range*/10);
    hero->place(starting_tile);

    // wall the border
    wall_border(floor);

    // make a hall
    int north_wall_row = starting_spot.row() - 2;
    int south_wall_row = starting_spot.row() + 2;
    make_wall(floor, Location(north_wall_row, 0), Location(north_wall_row, floor->width()-1));
    make_wall(floor, Location(south_wall_row, 0), Location(south_wall_row, floor->width()-1));

    // make north rooms
    static int min_room_width = 8;
    static int room_width_vary = 4;
    std::vector<int> north_walls_cells(1,0);
    srand(1);
    unsigned int wall_cell = min_room_width + (rand() % room_width_vary);
    while (wall_cell < floor->width() - (min_room_width-1)) {
        north_walls_cells.push_back(wall_cell);
        wall_cell += min_room_width + (rand() % room_width_vary);
    }
    north_walls_cells.push_back(floor->width()-1);

    for (int i = 1; i < static_cast<int>(north_walls_cells.size()); i++) {
        make_wall(floor, 
                  Location(0, north_walls_cells[i]), 
                  Location(north_wall_row-1, north_walls_cells[i]));

        // make door
        int door_cell = (north_walls_cells[i] - north_walls_cells[i-1])/2 + 
                        north_walls_cells[i-1];
        std::shared_ptr<Tile> tile = floor->tile(Location(north_wall_row,door_cell));
        std::shared_ptr<iThing> placed_wall = tile->thing(0);
        assert(placed_wall->content_size() == ContentSize::full);
        placed_wall->remove();
    }

    // add some stuff...
    // add 7 lights
    for (int i = 0; i < 7; i++) {
        int light_row = rand() % north_wall_row;
        int light_cell = rand() % floor->width();
        if (floor->tile(Location(light_row, light_cell))->how_full() != ContentSize::full) 
        {
            floor->add_light(light_row, light_cell, 20);
        }
        else
        {
            i--;
        }
    }

    std::shared_ptr<Rat> rat = std::make_shared<Rat>();
    int rat_row;
    int rat_cell;
    do {
        rat_row = rand() % north_wall_row;
        rat_cell = rand() % floor->width();
    } while(floor->tile(Location(rat_row, rat_cell))->how_full() == ContentSize::full);
    rat->place(floor->tile(Location(rat_row, rat_cell)));
    monsters.push_back(rat);

    std::shared_ptr<Bee> bee = std::make_shared<Bee>();
    int bee_row;
    int bee_cell;
    do {
        bee_row = rand() % north_wall_row;
        bee_cell = rand() % floor->width();
    } while(floor->tile(Location(bee_row, bee_cell))->how_full() == ContentSize::full);
    bee->place(floor->tile(Location(bee_row, bee_cell)));
    monsters.push_back(bee);

    // add a dog
    std::shared_ptr<Dog> dog = std::make_shared<Dog>();
    dog->place(floor->tile(Location(starting_spot.row(), starting_spot.cell()+1)));
    monsters.push_back(dog);

    return floor;
}

void wall_border(std::shared_ptr<Floor> floor)
{
    std::shared_ptr<Wall> wall;
    for (unsigned int row = 0; row < floor->height(); row++)
    {
        if (row == 0 || row == floor->height()-1)
        {
            for (unsigned int cell = 0; cell < floor->width(); cell++)
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

void make_wall(std::shared_ptr<Floor> floor, Location start, Location end)
{
    std::vector<Location> locations = bresenham_los(
        start.row(), start.cell(), end.row(), end.cell());

    std::shared_ptr<Wall> wall = std::make_shared<Wall>();
    for (auto& location : locations) {
        std::shared_ptr<Tile> tile = floor->tile(location);
        if (tile->there_is_room(wall)) {
            wall->place(tile);
            wall = std::make_shared<Wall>();
        }    
    }
}
