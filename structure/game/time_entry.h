#ifndef _time_entry_h_
#define _time_entry_h_

#include <memory>
#include "ithing.h"

//
// A single actor's entry in the timeline
//
class TimeEntry
{
public:
    TimeEntry(std::weak_ptr<iThing> actor, bool is_hero = false) : 
        actor_(actor), timestamp_(0), next_(nullptr), is_hero_(is_hero)
    {}

    // Get this actor
    std::weak_ptr<iThing> actor() { return this->actor_; }

    // Get the current timestamp
    unsigned long timestamp() { return this->timestamp_; }

    // Set the timestamp
    void set_timestamp(unsigned long timestamp) { this->timestamp_ = timestamp; }

    // Get the next
    std::shared_ptr<TimeEntry> next() { return this->next_; }

    // Set the next
    void set_next(std::shared_ptr<TimeEntry> next = nullptr) { this->next_ = next; }

    // this our hero
    bool is_hero() { return this->is_hero_; }

private:
    std::weak_ptr<iThing> actor_;
    unsigned long timestamp_;
    std::shared_ptr<TimeEntry> next_;
    bool is_hero_;
};

#endif // _time_entry_h_