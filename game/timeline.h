#ifndef _timeline_h_
#define _timeline_h_

#include <memory>
#include "time_entry.h"

//
// The ordered list of future actors
//
class TimeLine
{
public:
    TimeLine() : next_() {} 

    // insert an actor into the timeline
    void insert(std::shared_ptr<TimeEntry> entry, unsigned long time_added);

    // remove the next actor up from the timeline
    std::shared_ptr<TimeEntry> remove_next();

    // the timeline is empty 
    bool is_empty() const { return this->next_ == nullptr; }

private:
    std::shared_ptr<TimeEntry> next_;
};

#endif // _timeline_h_
