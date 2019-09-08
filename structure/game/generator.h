#ifndef _generator_h_
#define _generator_h_

#include <memory>
#include "game_type.h"
#include "iscreen.h"
#include "../world/floor.h"

//
// a static class for generating floors
//
class Generator
{
public:
    // create a floor to the user's specs
    static std::shared_ptr<Floor> make(
        std::shared_ptr<iScreen> screen,
        GameType game_type, 
        std::weak_ptr<Hero>& hero,
        std::vector<std::weak_ptr<iActor>>& actors);

private:
    // make the mini screen
    static std::shared_ptr<Floor> make_mini(
        std::shared_ptr<iScreen>, 
        std::weak_ptr<Hero>& hero, 
        std::vector<std::weak_ptr<iActor>>& actors);

    // make our standard testing floor
    static std::shared_ptr<Floor> make_test(
        std::shared_ptr<iScreen> screen, 
        std::weak_ptr<Hero>& hero, 
        std::vector<std::weak_ptr<iActor>>& actors);

    // make a real floor
    static std::shared_ptr<Floor> make_full(
        std::shared_ptr<iScreen> screen, 
        std::weak_ptr<Hero>& hero, 
        std::vector<std::weak_ptr<iActor>>& actors);

    // put a wall around a rectangular floor
    static void wall_border(std::shared_ptr<Floor>);

    // create a wall between two endpoints
    static void make_wall(std::shared_ptr<Floor> floor, Location start, Location end);
};

#endif // _generator_h_