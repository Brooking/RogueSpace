#include <assert.h>
#include <stdexcept>
#include "game.h"
#include "../ui/mosaic.h"
#include "../ui/statuspane.h"
#include "../ui/viewport.h"

Game::Game(std::shared_ptr<iScreen> screen, GameType game_type) : 
    floor_(), hero_(), mosaic_(), timeline_()
{
    // create the floor
    std::vector<std::weak_ptr<iActor>> actors;
    this->floor_ = Generator::make(screen, game_type, this->hero_, actors);

    // create the status window
    std::shared_ptr<StatusPane> status =
        std::make_shared<StatusPane>(
            screen,
            this->hero_,
            /*screen_row*/0, /*screen_cell*/0,
            screen->height());
    
    // create a viewport on that floor that is the viewable area
    std::shared_ptr<Viewport> viewport = 
        std::make_shared<Viewport>(
            screen, this->floor_, 
            /*screen_row*/0, /*screen_cell*/status->width(),
            screen->height(), 
            screen->width() - status->width(), 
            this->floor_->hero_location().row(),
            this->floor_->hero_location().cell());

    //put the UI items into the mosaic
   this->mosaic_ = std::make_shared<Mosaic>(screen);
    bool status_added = this->mosaic_->add(status);
    bool viewport_added = this->mosaic_->add(viewport);
    assert(status_added && viewport_added);
    this->floor_->register_update(this->mosaic_);
    this->mosaic_->refill();
    this->mosaic_->refresh();

    // fill up the timeline
    for (unsigned int i = 0; i < actors.size(); i++)
    {
        std::shared_ptr<iActor> actor = actors[i].lock();
        std::shared_ptr<TimeEntry> entry = std::make_shared<TimeEntry>(
            actor,
            actor.get() == dynamic_cast<iActor*>(this->hero_.lock().get()));
        this->timeline_.insert(entry, i);
    }
}

int Game::play()
{
    bool quit = false;
    while (!quit && !this->timeline_.is_empty())
    {
        std::shared_ptr<TimeEntry> entry = this->timeline_.remove_next();
        std::shared_ptr<iActor> actor = entry->actor().lock();
        if (actor == nullptr)
        {
            continue;
        }

        unsigned long time_used;
        if (entry->is_hero())
        {
            assert(entry->actor().lock() == this->hero_.lock());
            time_used = hero_move(quit);
        }
        else
        {
            time_used = actor->move();
        }
        this->mosaic_->refresh();
        this->timeline_.insert(entry, time_used);
    }

    return 0;
}

int Game::hero_move(bool& quit)
{
    // get and decode input
    for(;;)
    {
        unsigned int key = this->mosaic_->screen()->get_key_input();
        if (KeyToDirection.count(key) > 0)
        {
            Direction direction = KeyToDirection[key];
            return this->hero_.lock()->move(direction);
        }
        switch(key)
        {
            case 'q':
            case 'Q':
                // quit
                quit = true;
                return 0;

            case ' ':
                // space is stand for a turn
                return this->hero_.lock()->move();

            case 'r':
            case 'R':
                // toggle running
                this->hero_.lock()->toggle_run();

                // need to refresh because we are not returning,
                // but still want the UI to reflect the change
                this->mosaic_->refresh();
                continue;

            case '\t':
                // tab brings up map
                // todo
                continue;

            default:
                // for anything else, we go back for more input
                continue;
        }
    }
}

