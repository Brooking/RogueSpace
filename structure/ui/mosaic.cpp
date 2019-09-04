#include <bits/stdc++.h>
#include "blank_pane.h"
#include "mosaic.h"
#include "rect.h"

Mosaic::Mosaic(std::shared_ptr<io::Screen> screen) : 
    screen_(screen), panes_(), blank_pane_(), covered_panes_(),
    screen_row_(0), screen_cell_(0), height_(screen->height()), width_(screen->width())
{
    this->blank_pane_ = std::make_shared<BlankPane>(screen, 0, 0, screen->height(), screen->width());
}

bool Mosaic::update(unsigned int row, unsigned int cell, bool center)
{
    unsigned int passcount = 0;
    for(unsigned int i = 0; i < this->panes_.size(); i++)
    {
        if (this->panes_[i]->update(row, cell, center))
        {
            passcount++;
        }
    }

    return passcount == this->panes_.size();
}

bool Mosaic::update()
{
    unsigned int passcount = 0;
    for(unsigned int i = 0; i < this->panes_.size(); i++)
    {
        if (this->panes_[i]->update())
        {
            passcount++;
        }
    }

    return passcount == this->panes_.size();
}

void Mosaic::refill() 
{
    for (unsigned int i = 0; i < this->panes_.size(); i++)
    {
        this->panes_[i]->refill();
    }

    if (this->blank_pane_ != nullptr)
    {
        this->blank_pane_->refill();
    }
}

void Mosaic::refresh() 
{
    for (unsigned int i = 0; i < this->panes_.size(); i++)
    {
        this->panes_[i]->refresh();
    }

    if (this->blank_pane_ != nullptr)
    {
        this->blank_pane_->refresh();
    }
}

bool Mosaic::add(std::shared_ptr<iPane> pane)
{
    if (this->blank_pane_ == nullptr)
    {
        // no empty space
        return false;
    }

    Rect blank_rect(this->blank_pane_);
    Rect pane_rect(pane);
    bool fits = false;
    std::shared_ptr<Rect> remainder = blank_rect.subtract(pane_rect, fits);
    if (!fits)
    {
        // new pane does not fit in the empty space
        return false;
    }

    if (remainder == nullptr)
    {
        // new pane takes all space
        this->blank_pane_ = nullptr;
        this->panes_.push_back(pane);
        return true;
    }
    else
    {
        // new pane touches on three sides, leaving a rectangle
        this->blank_pane_ = std::make_shared<BlankPane>(
            this->screen_,
            remainder->screen_row(),
            remainder->screen_cell(),
            remainder->height(),
            remainder->width());
        this->panes_.push_back(pane);
        return true;
    }

    // new pane touches on 2 or fewer sides
    return false;
}

bool Mosaic::remove(std::shared_ptr<iPane> pane)
{
    // for now, we can only remove overlayed panes
    unsigned int removal_index = INT_MAX;
    for (unsigned int i = 0; i < this->covered_panes_.size(); i++)
    {
        if (this->panes_[i] == pane)
        {
            removal_index = i;
            break;
        }
    }

    if (removal_index == INT_MAX)
    {
        return false;
    }

    for (unsigned int i = 0; i < this->covered_panes_.size(); i++)
    {
        std::shared_ptr<iPane> covered = this->covered_panes_[i];
        if (pane->is_colocated_with(covered))
        {
            this->panes_[removal_index] = covered;
            this->covered_panes_.erase(this->covered_panes_.begin() + i);
            return true;
        }
    }
    return false;
}

bool Mosaic::overlay(std::shared_ptr<iPane> pane)
{
    // to overlay, the new pane must match size and position of an existing pane
    for (unsigned int i = 0; i < this->panes_.size(); i++)
    {
        std::shared_ptr<iPane> existing = this->panes_[i];
        if (pane->is_colocated_with(existing))
        {
            this->panes_[i] = pane;
            this->covered_panes_.push_back(existing);
            return true;
        }
    }

    return false;
}
