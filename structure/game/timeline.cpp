#include <bits/stdc++.h>
#include <stdexcept>
#include "timeline.h"

void TimeLine::insert(std::shared_ptr<TimeEntry> entry, unsigned long time_added)
{
    std::shared_ptr<TimeEntry> current;
    unsigned long space_left = ULONG_MAX - entry->timestamp();
    if (space_left <= time_added)
    {
        // we are about to wrap out timestamps, back everyone up
        unsigned long delta = entry->timestamp();
        if (this->next_ != nullptr)
        {            
            current = this->next_;
            delta = current->timestamp();
            if (delta < time_added - space_left)
            {
                // the space required exceeds the space available
                throw std::invalid_argument("Not enough room in the timeline");
            }
            while (current != nullptr)
            {
                current->set_timestamp(current->timestamp() - delta);
                current = current->next();
            }
        }
        entry->set_timestamp(entry->timestamp() - delta);
    }

    entry->set_timestamp(entry->timestamp() + time_added);

    if (this->next_ == nullptr || this->next_->timestamp() > entry->timestamp())
    {
        // insert at the head of the list
        entry->set_next(this->next_);
        this->next_ = entry;
        return;
    }

    // insert us in timestamp order
    current = this->next_;
    while (current->next() != nullptr && current->next()->timestamp() <= entry->timestamp())
    {
        current = current->next();
    }
    entry->set_next(current->next());
    current->set_next(entry);
}

std::shared_ptr<TimeEntry> TimeLine::remove_next()
{
    std::shared_ptr<TimeEntry> result;

    if (this->is_empty())
    {
        return result;
    }

    result = this->next_;
    this->next_ = result->next();
    result->set_next();

    return result;
}
