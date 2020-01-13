#include "thing_base.h"

UIToken ThingBase::token() const
{
    std::shared_ptr<Tile> tile = this->tile();
    if (tile == nullptr)
    {
        return UIToken(this->token_type_);
    }

    // Remembered items are set explicitly in their classes
    return UIToken(
        this->token_type_,
        tile->hero_can_see(),
        /*remembered*/false,
        tile->is_lit());
}

bool ThingBase::place(std::shared_ptr<Tile> tile)
{
    if (tile != nullptr && tile->there_is_room(this->shared_from_this()))
    {
        this->remove();
        tile->add(this->shared_from_this());
        this->tile_ = tile;
        return true;
    }

    return false;
}

bool ThingBase::remove()
{
    if (this->tile() != nullptr)
    {
        this->tile()->remove(this->shared_from_this());
        //this->tile_.reset();
    }

    return true;
}
