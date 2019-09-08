#ifndef _generator_h_
#define _generator_h_

#include <memory>
#include "iscreen.h"
#include "../world/floor.h"

// make the mini screen
std::shared_ptr<Floor> make_mini(
    std::shared_ptr<iScreen>, 
    std::weak_ptr<Hero>& hero, 
    std::vector<std::weak_ptr<iActor>>& actors);

// make our standard testing floor
std::shared_ptr<Floor> make_standard(
    std::shared_ptr<iScreen> screen, 
    std::weak_ptr<Hero>& hero, 
    std::vector<std::weak_ptr<iActor>>& actors);

// make a real floor
std::shared_ptr<Floor> make_full(
    std::shared_ptr<iScreen> screen, 
    std::weak_ptr<Hero>& hero, 
    std::vector<std::weak_ptr<iActor>>& actors);

#endif // _generator_h_