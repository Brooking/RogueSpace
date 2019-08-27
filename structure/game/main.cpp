#include <iostream>
#include <map>
#include <memory>
#include "io_constants.h"
#include "generator.h"
#include "../io/screen.h"
#include "../io/rawcurses.h"
#include "../ui/viewport.h"
#include "../world/floor.h"
#include "../world/hero.h"
#include "../world/wall.h"

void game_loop(std::shared_ptr<Viewport> viewport, std::shared_ptr<Hero> hero, std::vector<std::shared_ptr<iThing>> monsters);
void fill_floor(std::shared_ptr<Floor> floor, std::shared_ptr<Hero> hero);

int main()
{
    // initialize the screen
    std::shared_ptr<io::RawCurses> curses = std::make_shared<io::RawCurses>();
    std::shared_ptr<io::Screen> screen = io::Screen::open_screen(curses);

    // Print a welcome message and wait until the user presses a key
    screen->add("Welcome to the ", io::Color::YELLOW, io::Color::BLACK);
    screen->add("RogueSpace", io::Color::BRIGHT_YELLOW, io::Color::BLACK);
    screen->add("(tm) game.\n", io::Color::YELLOW, io::Color::BLACK);
    screen->add("1 - mini\n");
    screen->add("2 - standard\n");
    screen->add("3 - full\n");
    screen->add("If you want to quit, press \"Q\"\n\n");

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

    std::shared_ptr<Floor> floor = nullptr;
    std::shared_ptr<Hero> hero = nullptr;
    std::vector<std::shared_ptr<iThing>> monsters;
    do
    {
        int ch = screen->get_key_input();
        switch(ch)
        {
            case '1':
                floor = make_mini(screen, hero, monsters);
                break;

            case '2':
                floor = make_standard(screen, hero, monsters);
                break;

            case '3':
                floor = make_full(screen, hero, monsters);

            case 'q':
            case 'Q':
                // todo this should be done by screen destructor
                curses->endwin();
                return 0;
        }
    } while (floor == nullptr);
    
    // create a viewport on that floor that is the full viewable area
    std::shared_ptr<Viewport> viewport = 
        std::make_shared<Viewport>(
            screen, floor, 
            screen->height(), 
            screen->width(), 
            hero->where().row(),
            hero->where().cell());
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
