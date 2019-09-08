#include <assert.h>
#include <iostream>
#include <map>
#include <memory>
#include "game.h"
#include "io_constants.h"
#include "iscreen.h"
#include "../ui/io/rawcurses.h"
#include "../ui/io/screen.h"

void color_pallette(std::shared_ptr<iScreen> screen);

int main()
{
    // initialize the screen
    std::shared_ptr<iCurses> curses = std::make_shared<io::RawCurses>();
    std::shared_ptr<iScreen> screen = io::Screen::open_screen(curses);

    // Print a welcome message and wait until the user presses a key
    screen->add("Welcome to the ", io::Color::YELLOW, io::Color::BLACK);
    screen->add("RogueSpace", io::Color::BRIGHT_YELLOW, io::Color::BLACK);
    screen->add("(tm) game.\n", io::Color::YELLOW, io::Color::BLACK);
    screen->add("1 - mini\n");
    screen->add("2 - standard\n");
    screen->add("3 - full\n");
    screen->add("4 - color pallette\n");
    screen->add("If you want to quit, press \"Q\"\n\n");

    GameType game_type = GameType::none;
    do
    {
        unsigned int key = screen->get_key_input();
        switch(key)
        {
            case '1':
                game_type = GameType::mini;
                break;

            case '2':
                game_type = GameType::test;
                break;

            case '3':
                game_type = GameType::full;
                break;

            case '4':
                color_pallette(screen);
                return 0;

            case 'q':
            case 'Q':
                return 0;

            default:
                break;
        }
    } while (game_type == GameType::none);

    Game game(screen, game_type);
    int result = game.play();
    return result;
}

void color_pallette(std::shared_ptr<iScreen> screen)
{
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
    screen->get_key_input();
}

