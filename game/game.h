#ifndef _game_h_
#define _game_h_

#include <memory>
#include "game_type.h"
#include "generator.h"
#include "iactor.h"
#include "ifloor.h"
#include "iscreen.h"
#include "timeline.h"
#include "../ui/mosaic.h"
#include "../world/hero.h" // todo - should be an interface

//
// A game of roguespace
//
class Game final
{
public:
    Game(std::shared_ptr<iScreen> screen, GameType game_type);
    ~Game() {}

    // play the game
    int play();

private:
    // ask the player about the hero's next move
    unsigned int hero_move(bool& quit);

private:
    std::shared_ptr<iFloor> floor_;
    std::weak_ptr<Hero> hero_;
    std::shared_ptr<Mosaic> mosaic_;
    TimeLine timeline_;
};

#endif // _game_h_