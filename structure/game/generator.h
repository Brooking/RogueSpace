#ifndef _generator_h_
#define _generator_h_

#include <memory>
#include "iscreen.h"
#include "../world/floor.h"

// make the mini screen
std::shared_ptr<Floor> make_mini(
    std::shared_ptr<iScreen>, 
    std::shared_ptr<Hero>& hero, 
    std::vector<std::shared_ptr<iThing>>&);

// make our standard testing floor
std::shared_ptr<Floor> make_standard(
    std::shared_ptr<iScreen> screen, 
    std::shared_ptr<Hero>& hero, 
    std::vector<std::shared_ptr<iThing>>& monsters);

// make a real floor
std::shared_ptr<Floor> make_full(
    std::shared_ptr<iScreen> screen, 
    std::shared_ptr<Hero>& hero, 
    std::vector<std::shared_ptr<iThing>>& monsters);

#endif // _generator_h_