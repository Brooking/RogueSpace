#include <iostream>
#include "catch.hpp"
#include "icurses_mock.h"
#include "iscreen.h"
#include "../ui/io/screen.h"


TEST_CASE("screen_withGoingOutOfScope_shouldDestruct", "[screen]")
{
    bool destructor_called = false;
    {
        // arrange
        std::shared_ptr<iCurses> curses = std::make_shared<iCursesMock>(&destructor_called);
        std::shared_ptr<iScreen> screen = io::Screen::open_screen(curses);

        // act
        // the action is the screen going out of scope
    }

    // assert
    REQUIRE(destructor_called == true);
}
