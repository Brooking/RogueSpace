#include <assert.h>
#include "floor.h"
#include "fov.h"
#include "tile.h"

UIToken Tile::token()
{
    std::shared_ptr<Floor> floor = this->floor();
    if (floor == nullptr)
    {
        return UIToken();
    }

    std::weak_ptr<Hero> hero = floor->hero();
    if (floor->hero().expired())
    {
        return UIToken();
    }

    bool hero_can_see = this->hero_can_see();
    if (hero_can_see)
    {
        // This is the spot where we update tiles that the hero has
        // seen. Asking for the token is as good a place as any.
        this->has_been_seen_ = true;
    }

    if (this->num_things() > 0)
    {
        UIToken token = this->things_.back()->token();
        if (token.is_visible() || token.is_remembered())
        {
            return token;
        }
    }

    return UIToken(
        TokenType::floor,
        hero_can_see,
        this->has_been_seen(), // floors are remembered once seen
        this->is_lit());
}


bool Tile::add(std::shared_ptr<iThing> thing)
{
    if (thing != nullptr)
    {
        if (this->there_is_room(thing))
        {
            this->things_.push_back(thing);
            this->fullness_ = this->calculate_fullness();
            if (!this->floor_.expired())
            {
                this->floor()->update(this->location_, thing->is_center());
            }
            return true;
        }
    }
    
    return false;
}

bool Tile::remove(std::shared_ptr<iThing> thing)
{
    if (thing == nullptr) 
    {
        return false;
    }

    bool thing_found = false;
    for (size_t i = 0; i < this->things_.size(); i++) 
    {
        if (this->things_[i] == thing) 
        {
            thing_found = true;
            this->things_.erase(this->things_.begin()+i);
            this->fullness_ = this->calculate_fullness();
            if (!this->floor_.expired())
            {
                this->floor()->update(this->location_);
            }
            break;
        }
    }

    return thing_found;
}

ContentSize Tile::calculate_fullness()
{
    ContentSize size = ContentSize::empty;
    for (auto thing : this->things_)
    {
        if (static_cast<unsigned int>(thing->content_size()) > static_cast<unsigned int>(size))
        {
            size = thing->content_size();
        }
    }

    return size;
}

bool Tile::there_is_room(std::shared_ptr<iThing> thing)
{
    assert(thing->content_size() != ContentSize::empty);

    if (this->fullness_ == ContentSize::empty)
    {
        return true;
    }

    if (this->fullness_ == ContentSize::small)
    {
        return thing->content_size() != ContentSize::full;
    }

    if (this->fullness_ == ContentSize::large)
    {
        return thing->content_size() == ContentSize::small;
    }

    assert(this->fullness_ == ContentSize::full);
    return false;
}

void Tile::add_los_range(Location location, unsigned int range)
{
    (*this->los_range_)[location.row()][location.cell()] = range;
}

unsigned int Tile::get_los_range(Location location)
{
    if (this->los_range_ == nullptr)
    {
        this->los_range_ = 
            new std::vector<std::vector<unsigned int>>(
                this->floor()->height(), 
                std::vector<unsigned int>(
                    this->floor()->width(), 
                    UINT_MAX
                )
            );
        
        std::shared_ptr<iFov> fov = std::make_shared<EyeLos>(this->shared_from_this());
        std::shared_ptr<iWallMap> map = this->floor();
        Fov::do_fov(fov, map, this->where().row(), this->where().cell());
    }

    return ((*this->los_range_)[location.row()][location.cell()]);
}

bool Tile::hero_can_see()
{
    std::shared_ptr<Floor> floor = this->floor();
    if (floor == nullptr)
    {
        return false;
    }
    std::shared_ptr<Hero> hero = floor->hero().lock();
    if (hero == nullptr)
    {
        return false;
    }
    return hero->can_see(this->where());
}

bool Tile::is_wall()
{
    if (this->things_.size() > 0  &&
        this->things_[0]->token_type() == TokenType::wall)
    {
        assert(this->how_full() == ContentSize::full);
        assert(this->things_.size() == 1);
        return true;
    }
    return false;
}

